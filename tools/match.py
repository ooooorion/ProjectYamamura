#!/usr/bin/env python3
"""Byte-match decompiled functions against the shipped Block.elf.

    python tools/match.py                     # every row in src/functions.tsv
    python tools/match.py func_02015FCC       # one function
    python tools/match.py --sweep             # try several -O levels

Each row names one source file that defines one function. The file is compiled
with Green Hills ccppc, the object's .text for that symbol is compared word for
word against the target range in Block.elf, and the first differing word is
reported. A function counts as matched only when every byte is equal and the
sizes agree.

Object relocations in the function range are applied from config/symbols.txt
before the bytes are compared. A row is BLOCKED only when unresolved
relocations could account for every remaining difference; a difference outside
those sites is DIFF. An unresolved relocation is never treated as a match.

If the compiler is missing or unlicensed, this stops and prints its error. An
unverified function is reported as unverified, never as a match.
"""
from __future__ import annotations

import argparse
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCLUDE_DIR = os.path.join(ROOT, "include")
DEFAULT_ELF = os.environ.get("SMM_ELF", os.path.join("orig", "Block.elf"))
DEFAULT_CC = os.environ.get("CCPPC", "ccppc")
DEFAULT_CFLAGS = "-c -O2"
DEFAULT_TABLE = os.path.join(ROOT, "src", "functions.tsv")
DEFAULT_SYMBOLS = os.path.join(ROOT, "config", "symbols.txt")
SWEEP = ["-O1", "-O2", "-O3", "-Ogeneral", "-Ospeed", "-Ospace"]

R_PPC_ADDR32 = 1
R_PPC_ADDR24 = 2
R_PPC_ADDR16 = 3
R_PPC_ADDR16_LO = 4
R_PPC_ADDR16_HI = 5
R_PPC_ADDR16_HA = 6
R_PPC_REL24 = 10
R_PPC_REL14 = 11
R_PPC_REL32 = 26


class Elf:
    """Just enough ELF32 big-endian to find sections, bytes and symbols."""

    def __init__(self, path):
        self.path = path
        with open(path, "rb") as f:
            self.data = f.read()
        b = self.data
        if b[:4] != b"\x7fELF" or b[4] != 1 or b[5] != 2:
            raise SystemExit("%s: not a 32-bit big-endian ELF" % path)
        shoff = struct.unpack_from(">I", b, 32)[0]
        shentsize = struct.unpack_from(">H", b, 46)[0]
        shnum = struct.unpack_from(">H", b, 48)[0]
        shstrndx = struct.unpack_from(">H", b, 50)[0]
        raw = [struct.unpack_from(">IIIIIIIIII", b, shoff + i * shentsize)
               for i in range(shnum)]
        stoff = raw[shstrndx][4]
        self.sections = []
        for r in raw:
            self.sections.append({
                "name": self._name(stoff, r[0]),
                "type": r[1],
                "addr": r[3],
                "off": r[4],
                "size": r[5],
                "link": r[6],
                "entsize": r[9],
            })

    def _name(self, strtab_off, nameoff):
        start = strtab_off + nameoff
        end = self.data.find(b"\0", start)
        return self.data[start:end].decode("ascii", "replace")

    def section(self, name):
        for s in self.sections:
            if s["name"] == name:
                return s
        return None

    def read(self, vaddr, size):
        for s in self.sections:
            if s["type"] == 8:              # SHT_NOBITS: no bytes on disk
                continue
            if s["addr"] <= vaddr and vaddr + size <= s["addr"] + s["size"]:
                start = s["off"] + (vaddr - s["addr"])
                return self.data[start:start + size]
        raise SystemExit("no section covers %08X+%d" % (vaddr, size))

    def symbols(self):
        """All .symtab entries, in index order."""
        symtab = self.section(".symtab")
        if symtab is None:
            return []
        strtab = self.sections[symtab["link"]]
        entsize = symtab["entsize"] or 16
        out = []
        for o in range(symtab["off"], symtab["off"] + symtab["size"], entsize):
            nameoff, value, size, info, other, shndx = struct.unpack_from(
                ">IIIBBH", self.data, o)
            out.append({
                "name": self._name(strtab["off"], nameoff),
                "value": value,
                "size": size,
                "info": info,
                "shndx": shndx,
            })
        return out

    def symbol(self, name):
        for sym in self.symbols():
            if sym["name"] == name:
                return sym["value"], sym["size"]
        return None, None

    def relocations(self, name=".rela.text"):
        """RELA records for a section, in file order."""
        rela = self.section(name)
        if rela is None:
            return []
        entsize = rela["entsize"] or 12
        out = []
        for o in range(rela["off"], rela["off"] + rela["size"], entsize):
            offset, info, addend = struct.unpack_from(">III", self.data, o)
            out.append({
                "offset": offset,
                "sym": info >> 8,
                "type": info & 0xFF,
                "addend": addend,
            })
        return out


def load_table(path):
    rows = []
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split("\t")
            if len(parts) < 4 or len(parts) > 5:
                raise SystemExit(
                    "%s: expected name<TAB>start<TAB>end<TAB>source[<TAB>cflags]" % path)
            flags = parts[4] if len(parts) == 5 else ""
            rows.append((parts[0], int(parts[1], 16), int(parts[2], 16),
                         parts[3], flags))
    return rows


def load_symbols(path):
    symbols = {}
    if not path:
        return symbols
    with open(path, encoding="utf-8") as f:
        for line in f:
            m = re.match(r"^\s*([A-Za-z_]\w*)\s*=\s*0x([0-9A-Fa-f]+)\s*;", line)
            if m:
                symbols[m.group(1)] = int(m.group(2), 16)
    return symbols


def symbol_value(elf, symbols, name):
    if not name:
        return None
    m = re.match(r"func_([0-9A-Fa-f]{8})$", name)
    if m:
        return int(m.group(1), 16)
    if name in symbols:
        return symbols[name]
    value, _size = elf.symbol(name)
    return value if value else None


def relocation_width(kind):
    """Number of bytes a relocation can rewrite at its site."""
    if kind in (R_PPC_ADDR16, R_PPC_ADDR16_LO, R_PPC_ADDR16_HI,
                R_PPC_ADDR16_HA):
        return 2
    return 4


def apply_relocations(blob, target_start, obj_elf, obj_value, symbols, target_elf):
    """Apply one object's .rela.text records to its function bytes.

    Returns (bytes, applied, unresolved, unresolved_sites). The sites are
    (offset, width) pairs, so the caller can distinguish a raw-byte mismatch
    from a difference that an unresolved relocation might still explain.
    Unresolved entries are reported by the caller and never treated as a
    match.
    """
    data = bytearray(blob)
    object_symbols = obj_elf.symbols()
    applied = []
    unresolved = []
    unresolved_sites = []
    for rel in obj_elf.relocations(".rela.text"):
        local = rel["offset"] - obj_value
        if local < 0 or local >= len(blob):
            continue
        kind = rel["type"]
        width = relocation_width(kind)
        index = rel["sym"]
        if index >= len(object_symbols):
            unresolved.append("bad symbol index %d" % index)
            unresolved_sites.append((local, width))
            continue
        name = object_symbols[index]["name"]
        base = symbol_value(target_elf, symbols, name)
        if base is None:
            unresolved.append("%s@+0x%X" % (name or "<unnamed>", local))
            unresolved_sites.append((local, width))
            continue
        addend = rel["addend"]
        if addend & 0x80000000:
            addend -= 0x100000000
        value = base + addend
        place = target_start + local
        if kind == R_PPC_ADDR32:
            struct.pack_into(">I", data, local, value & 0xFFFFFFFF)
        elif kind == R_PPC_ADDR16_HA:
            struct.pack_into(">H", data, local, ((value + 0x8000) >> 16) & 0xFFFF)
        elif kind == R_PPC_ADDR16_LO:
            struct.pack_into(">H", data, local, value & 0xFFFF)
        elif kind == R_PPC_ADDR16_HI:
            struct.pack_into(">H", data, local, (value >> 16) & 0xFFFF)
        elif kind == R_PPC_ADDR16:
            struct.pack_into(">H", data, local, value & 0xFFFF)
        elif kind == R_PPC_REL24:
            word = struct.unpack_from(">I", data, local)[0]
            disp = (value - place) & 0x03FFFFFC
            struct.pack_into(">I", data, local, (word & 0xFC000003) | disp)
        elif kind == R_PPC_REL14:
            word = struct.unpack_from(">I", data, local)[0]
            disp = (value - place) & 0x0000FFFC
            struct.pack_into(">I", data, local, (word & 0xFFFF0003) | disp)
        elif kind == R_PPC_ADDR24:
            word = struct.unpack_from(">I", data, local)[0]
            struct.pack_into(">I", data, local,
                             (word & 0xFC000003) | (value & 0x03FFFFFC))
        elif kind == R_PPC_REL32:
            struct.pack_into(">I", data, local, (value - place) & 0xFFFFFFFF)
        else:
            unresolved.append("%s@+0x%X type %d" % (name or "<unnamed>", local, kind))
            unresolved_sites.append((local, width))
            continue
        applied.append((local, kind, name))
    return bytes(data), applied, unresolved, unresolved_sites


def object_bytes(path, symbol):
    elf = Elf(path)
    text = elf.section(".text")
    if text is None:
        raise SystemExit("%s: no .text section" % path)
    blob = elf.data[text["off"]:text["off"] + text["size"]]
    value, size = elf.symbol(symbol)
    if value is None:
        return blob
    return blob[value:value + size] if size else blob[value:]


def compare(target, got):
    total = min(len(target), len(got)) // 4
    same = 0
    first = None
    for i in range(total):
        if target[i * 4:i * 4 + 4] == got[i * 4:i * 4 + 4]:
            same += 1
        elif first is None:
            first = i
    exact = len(target) == len(got) and same == total
    return same, total, first, exact


def classify(target, got, unresolved_sites=()):
    """Classify a comparison, using unresolved relocation sites as uncertainty.

    Returns (status, same, total, first, exact). A difference outside every
    unresolved site is DIFF: no relocation can explain it. If the only
    differences lie inside unresolved sites (or there are none at all), the
    result is BLOCKED, because those bytes could still change. An unresolved
    relocation is never treated as a match.
    """
    same, total, first, exact = compare(target, got)
    if not unresolved_sites:
        return ("MATCH" if exact else "DIFF"), same, total, first, exact

    if len(target) != len(got):
        return "DIFF", same, total, first, False

    unresolved = bytearray(len(got))
    for local, width in unresolved_sites:
        for i in range(max(0, local), min(len(unresolved), local + width)):
            unresolved[i] = 1

    first_outside = None
    for i in range(total):
        base = i * 4
        for j in range(4):
            if (target[base + j] != got[base + j] and
                    not unresolved[base + j]):
                first_outside = i
                break
        if first_outside is not None:
            break
    if first_outside is not None:
        return "DIFF", same, total, first_outside, False
    return "BLOCKED", same, total, None, False


def compile_one(cc, flags, src, out):
    cmd = [cc] + flags.split() + ["-I" + INCLUDE_DIR, src, "-o", out]
    return subprocess.run(cmd, capture_output=True, text=True)


def run(args):
    elf = Elf(args.elf)
    rows = load_table(args.table)
    symbols = load_symbols(args.symbols)
    if args.name:
        wanted = set(args.name)
        rows = [r for r in rows if r[0] in wanted]
        if not rows:
            raise SystemExit("no matching function in %s" % args.table)
    os.makedirs(args.outdir, exist_ok=True)
    flag_sets = args.cflags.split("|") if args.cflags else [DEFAULT_CFLAGS]
    if args.sweep:
        flag_sets = ["-c " + f for f in SWEEP]

    best = {}
    failed = False
    for flags in flag_sets:
        if args.sweep:
            print("== flags: %s" % flags)
        for name, start, end, src, row_flags in rows:
            obj = os.path.join(args.outdir, name + ".o")
            compile_flags = row_flags if row_flags and not args.sweep else flags
            result = compile_one(args.cc, compile_flags, os.path.join(ROOT, src), obj)
            if result.returncode != 0:
                lines = (result.stderr or result.stdout).strip().splitlines()
                print("BLOCKED %s: compiler failed (exit %d)" % (name, result.returncode))
                for line in lines[:8]:
                    print("   " + line)
                return 2
            target = elf.read(start, end - start + 4)
            obj_elf = Elf(obj)
            obj_value, _obj_size = obj_elf.symbol(name)
            got = object_bytes(obj, name)
            applied = []
            unresolved = []
            unresolved_sites = []
            if obj_value is not None:
                got, applied, unresolved, unresolved_sites = apply_relocations(
                    got, start, obj_elf, obj_value, symbols, elf)
            status, same, total, first, _exact = classify(
                target, got, unresolved_sites)
            best[name] = max(best.get(name, (0, 0)), (same, total))
            suffix = " [%d relocs]" % len(applied) if applied else ""
            if status == "BLOCKED":
                print("BLOCKED %s: unresolved relocations: %s"
                      % (name, ", ".join(unresolved[:4])))
                if args.sweep:
                    continue
                return 2
            if status == "MATCH":
                print("%-16s %3d B  MATCH%s" % (name, len(target), suffix))
                continue
            detail = "%d/%d words" % (same, total)
            if applied:
                detail += ", %d relocs applied" % len(applied)
            if unresolved:
                detail += ", %d unresolved" % len(unresolved)
            if first is not None:
                detail += ", first diff at +0x%X" % (first * 4)
            if len(target) != len(got):
                detail += ", size %d vs %d" % (len(target), len(got))
            print("%-16s %3d B  diff %s" % (name, len(target), detail))
            if first is not None:
                print("    target %s" % target[first * 4:first * 4 + 4].hex(" "))
                print("    object %s" % got[first * 4:first * 4 + 4].hex(" "))
            if not args.sweep:
                failed = True

    if args.sweep:
        print("== best per function")
        for name, (same, total) in best.items():
            print("%-16s %d/%d words" % (name, same, total))
    return 2 if failed else 0


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Byte-match decompiled functions against Block.elf.")
    ap.add_argument("name", nargs="*", help="function name(s) to check")
    ap.add_argument("--elf", default=DEFAULT_ELF, help="reference ELF")
    ap.add_argument("--cc", default=DEFAULT_CC, help="Green Hills C compiler")
    ap.add_argument("--cflags", default=DEFAULT_CFLAGS,
                    help="default compiler flags; split alternatives with '|'")
    ap.add_argument("--table", default=DEFAULT_TABLE, help="function table")
    ap.add_argument("--symbols", default=DEFAULT_SYMBOLS,
                    help="name = 0xADDRESS map for relocation symbols")
    ap.add_argument("--outdir", default=os.path.join(ROOT, "build"))
    ap.add_argument("--sweep", action="store_true",
                    help="try common optimization levels and report the best")
    return run(ap.parse_args(argv))


if __name__ == "__main__":
    sys.exit(main())
