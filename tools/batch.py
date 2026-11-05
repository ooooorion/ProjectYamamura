#!/usr/bin/env python3
"""Run the m2c candidate loop over eligible functions in an address band.

    python tools/batch.py                       # 50 from 0x02050000
    python tools/batch.py 02050000 02090000 --limit 50
    python tools/batch.py 02050000 02090000 --opt -O3
    python tools/batch.py 02050000 02090000 --allow-calls --max-insn 60

Candidates are found the same way as the manual passes: function starts are
internal `bl` targets, the extent runs to the next start, the last instruction
must be `blr`, and the body must avoid access through r2. By default the body
must also be a leaf with every branch internal. With --allow-calls, direct
`bl` calls are accepted and their REL24 relocations are applied before the
comparison; absolute and conditional-link calls remain ineligible.

Each candidate is sliced, decompiled by m2c, compiled with GHS and compared
word for word, with the object's relocations applied. Results are written to
build/batch/results.tsv and summarised on stdout. A MATCH means equal bytes
and equal size; everything else is DIFF, COMPILE or BLOCKED and is not a match.
"""
from __future__ import annotations

import argparse
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import crack
import fn2m2c
import match

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTDIR = os.path.join(ROOT, "build", "batch")
NAMED_RE = re.compile(r"(?<=\s)([0-9a-f]{5,8})(?=\s|$)")


def load_listing(path):
    addresses = {}
    with open(path, encoding="ascii", errors="replace") as f:
        for line in f:
            m = re.match(r"^\s*([0-9a-f]+):\t(.*)$", line.rstrip("\r\n"))
            if m:
                addresses[int(m.group(1), 16)] = m.group(2).strip()
    return addresses


def discover(asm, lo, hi, min_insn, max_insn, allow_calls=False,
             calls_only=False):
    addresses = load_listing(asm)
    inside = [a for a in sorted(addresses) if 0x02000020 <= a <= 0x02C6E298]
    starts = set()
    for addr in inside:
        text = addresses[addr]
        if text.split()[0] not in ("bl", "bla", "bcl"):
            continue
        m = NAMED_RE.search(text)
        if m:
            target = int(m.group(1), 16)
            if 0x02000020 <= target <= 0x02C6E298:
                starts.add(target)
    ordered = sorted(starts)
    candidates = []
    for i, start in enumerate(ordered):
        if not (lo <= start < hi):
            continue
        nxt = ordered[i + 1] if i + 1 < len(ordered) else None
        if nxt is None:
            continue
        size = nxt - start
        if size < 4 * min_insn or size > 4 * max_insn:
            continue
        count = size // 4
        body = [addresses.get(start + 4 * k) for k in range(count)]
        if any(text is None for text in body):
            continue
        if body[-1].split()[0] != "blr":
            continue
        # A run of nothing but blr is alignment padding after a real function,
        # not a leaf that happens to start at a bl target.
        if count > 1 and all(text.split()[0] == "blr" for text in body):
            continue
        eligible = True
        has_call = False
        for text in body:
            mnemonic = text.split()[0]
            if re.search(r"\br2\b", text):
                eligible = False
                break
            if mnemonic in ("bl", "bla", "bcl"):
                if mnemonic == "bl":
                    has_call = True
                if not allow_calls or mnemonic != "bl":
                    eligible = False
                    break
                m = NAMED_RE.search(text)
                if not m:
                    eligible = False
                    break
                target = int(m.group(1), 16)
                if not (0x02000020 <= target <= 0x02C6E298 or
                        0x02C6E2A8 <= target <= 0x02C77078):
                    eligible = False
                    break
                continue
            if mnemonic.startswith("b") and mnemonic not in (
                    "bctrl", "blrl", "blr"):
                m = NAMED_RE.search(text)
                if not m or not (start <= int(m.group(1), 16)
                                 <= start + 4 * (count - 1)):
                    eligible = False
                    break
        if calls_only and not has_call:
            eligible = False
        if eligible:
            candidates.append((start, start + 4 * (count - 1), count))
    return candidates


def generate(start, end, args):
    insns = fn2m2c.slice_function(args.asm, start, end)
    if not insns:
        return None, None, "no instructions in listing"
    asm_text, label = fn2m2c.render(insns)
    asm_path = os.path.join(OUTDIR, label + ".s")
    crack.write_text(asm_path, asm_text)
    command = [sys.executable, args.m2c, "-t", args.target, "-f", label,
               "--valid-syntax"] + args.m2c_arg + [asm_path]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        message = (result.stderr or result.stdout).strip().splitlines()
        return None, label, message[0] if message else "m2c failed"
    body = crack.fix_indexed_fields(result.stdout.replace("\r\n", "\n")).rstrip()
    if not body.strip():
        return None, label, "m2c produced no source"
    text = crack.CANDIDATE_HEADER % (start, end, crack.m2c_macros(args.m2c), body)
    crack.write_text(os.path.join(OUTDIR, label + ".c"), text)
    return text, label, None


def compare(elf, symbols, start, target, object_path, name):
    obj_elf = match.Elf(object_path)
    value, _size = obj_elf.symbol(name)
    if value is None:
        return "NO-SYMBOL", 0, 0, None, None
    got = match.object_bytes(object_path, name)
    got, applied, unresolved = match.apply_relocations(
        got, start, obj_elf, value, symbols, elf)
    if unresolved:
        return "BLOCKED", 0, 0, None, unresolved[0]
    same, total, first, exact = match.compare(target, got)
    return ("MATCH" if exact else "DIFF"), same, total, first, None


def run(args):
    lo, hi = fn2m2c.parse_addr(args.lo), fn2m2c.parse_addr(args.hi)
    candidates = discover(args.asm, lo, hi, args.min_insn, args.max_insn,
                          args.allow_calls, args.calls_only)
    if args.limit:
        candidates = candidates[:args.limit]
    if not candidates:
        raise SystemExit("no eligible functions in 0x%08X..0x%08X" % (lo, hi))
    os.makedirs(OUTDIR, exist_ok=True)

    elf = match.Elf(args.elf)
    symbols = match.load_symbols(args.symbols)
    rows = []
    print("%d candidates in 0x%08X..0x%08X at %s"
          % (len(candidates), lo, hi, args.opt))
    for start, end, count in candidates:
        name = "func_%08X" % start
        target = elf.read(start, end - start + 4)
        text, label, error = generate(start, end, args)
        status, same, total, first, detail = "COMPILE", 0, 0, None, error
        if text is not None:
            object_path = os.path.join(OUTDIR, name + ".o")
            compiled = crack.compile_one(args.cc, args.opt,
                                         os.path.join(OUTDIR, label + ".c"),
                                         object_path)
            if compiled.returncode:
                lines = (compiled.stderr or compiled.stdout).strip().splitlines()
                detail = lines[0] if lines else "compiler failed"
            else:
                status, same, total, first, detail = compare(
                    elf, symbols, start, target, object_path, name)
        rows.append((name, start, end, len(target), status, same, total,
                     first, detail))
        suffix = ""
        if total:
            suffix = " %d/%d words" % (same, total)
        if first is not None:
            suffix += " +0x%X" % (first * 4)
        if detail:
            suffix += " " + detail
        print("%-16s %3d B  %-9s%s" % (name, len(target), status, suffix))

    counts = {}
    for row in rows:
        counts[row[4]] = counts.get(row[4], 0) + 1
    print("== " + ", ".join("%s %d" % (k, counts[k]) for k in sorted(counts)))
    print("== %d/%d exact" % (counts.get("MATCH", 0), len(rows)))

    path = os.path.join(OUTDIR, "results.tsv")
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# name\tstart\tend\tbytes\tstatus\twords\ttotal\tfirst_diff\tdetail\n")
        for name, start, end, size, status, same, total, first, detail in rows:
            f.write("%s\t%08X\t%08X\t%d\t%s\t%d\t%d\t%s\t%s\n"
                    % (name, start, end, size, status, same, total,
                       "" if first is None else "+0x%X" % (first * 4),
                       (detail or "").replace("\t", " ")))
    print("== %s" % path)
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Decompile and byte-check eligible functions in a band.")
    ap.add_argument("lo", nargs="?", default="02050000", help="first address")
    ap.add_argument("hi", nargs="?", default="02090000", help="end address, exclusive")
    ap.add_argument("--limit", type=int, default=50, help="candidates to try (0 = all)")
    ap.add_argument("--min-insn", type=int, default=2)
    ap.add_argument("--max-insn", type=int, default=18)
    ap.add_argument("--allow-calls", action="store_true",
                    help="accept direct bl calls and apply their relocations")
    ap.add_argument("--calls-only", action="store_true",
                    help="only select call-bearing functions; requires --allow-calls")
    ap.add_argument("--opt", default="-O2", help="optimisation flag")
    ap.add_argument("--asm", default=fn2m2c.DEFAULT_ASM, help="main.s listing")
    ap.add_argument("--m2c", default=fn2m2c.DEFAULT_M2C, help="path to m2c.py")
    ap.add_argument("--m2c-arg", action="append", default=[], metavar="ARG",
                    help="extra m2c argument, repeatable")
    ap.add_argument("--cc", default=match.DEFAULT_CC, help="Green Hills ccppc")
    ap.add_argument("--elf", default=match.DEFAULT_ELF, help="reference Block.elf")
    ap.add_argument("--symbols", default=match.DEFAULT_SYMBOLS,
                    help="relative symbol map for relocations")
    ap.add_argument("-t", "--target", default="ppc", help="m2c target")
    args = ap.parse_args(argv)
    if args.calls_only and not args.allow_calls:
        ap.error("--calls-only requires --allow-calls")
    return run(args)


if __name__ == "__main__":
    sys.exit(main())
