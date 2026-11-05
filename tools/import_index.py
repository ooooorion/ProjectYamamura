"""Index the Wii U RPL import stubs of Block.elf and every call site that reaches them.

Do not try to find these by scanning `.text` for branches.  The import stubs
live at 0xC0000000+, which is far outside the +/-32 MB reach of a `bl` from
`.text`, so the displacement encoded in the file is a placeholder that the RPL
loader patches at load time.  Every real call site instead carries an
R_PPC_REL24 relocation whose symbol *is* the import, so `.rela.text` is the
authoritative caller -> import map.

  python tools/import_index.py
    -> asm/imports_by_name.tsv   (calls, module, name, stub)
    -> asm/import_calls.tsv       (caller, kind, module, name, stub)
"""

import io
import os
import struct
import sys
from collections import Counter, defaultdict

ELF = os.environ.get("SMM_ELF", os.path.join("orig", "Block.elf"))
OUT_DIR = os.environ.get("SMM_ASM", "asm")

SHT_SYMTAB = 2
R_PPC_ADDR16_HI = 5
R_PPC_ADDR16_HA = 6
R_PPC_REL24 = 10


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    data = open(ELF, "rb").read()

    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        sys.exit("not a 32-bit big-endian ELF")

    (_etype, _emach, _ver, _entry, _phoff, e_shoff, _flags,
     _ehsize, _phentsize, _phnum, e_shentsize, e_shnum, e_shstrndx) = \
        struct.unpack_from(">HHIIIIIHHHHHH", data, 16)

    shdrs = [list(struct.unpack_from(">IIIIIIIIII", data, e_shoff + i * e_shentsize))
             for i in range(e_shnum)]
    shstr = shdrs[e_shstrndx][4]

    def sh_name(i):
        start = shstr + shdrs[i][0]
        return data[start:data.index(b"\0", start)].decode("ascii", "replace")

    names = [sh_name(i) for i in range(e_shnum)]

    symtab = next(s for s in shdrs if s[1] == SHT_SYMTAB)
    strtab = shdrs[symtab[6]][4]

    def sym_name(off):
        start = strtab + off
        return data[start:data.index(b"\0", start)].decode("ascii", "replace")

    # ---- import symbols: named entries living in a .fimport_* section ----
    # These are STT_OBJECT / STB_WEAK, not STT_FUNC, so filter on the section.
    imports = {}                       # symbol index -> (module, name, stub)
    for i, off in enumerate(range(symtab[4], symtab[4] + symtab[5], 16)):
        st_name, st_value, _size, st_info, _other, st_shndx = \
            struct.unpack_from(">IIIBBH", data, off)
        if st_name == 0 or st_shndx == 0 or st_shndx >= e_shnum:
            continue
        sec = names[st_shndx]
        if not sec.startswith(".fimport_"):
            continue
        name = sym_name(st_name)
        if name == sec:                # the section symbol itself
            continue
        imports[i] = (sec[len(".fimport_"):], name, st_value)

    print(f"import symbols: {len(imports)}")

    # ---- every relocation in .rela.text that targets an import ----
    rela, text = shdrs[7], shdrs[2]
    tbase = text[3]
    tdata = data[text[4]:text[4] + text[5]]

    calls = []                         # (caller, kind, module, name, stub)
    taken = Counter()                  # address-taken imports (lis/addi pairs)
    stray = Counter()
    for off in range(rela[4], rela[4] + rela[5], 12):
        r_offset, r_info, _addend = struct.unpack_from(">III", data, off)
        sym = r_info >> 8
        rtype = r_info & 0xFF
        entry = imports.get(sym)
        if entry is None:
            continue
        if rtype in (R_PPC_ADDR16_HI, R_PPC_ADDR16_HA):
            taken[entry[1:]] += 1
            continue
        if rtype != R_PPC_REL24:
            stray[rtype] += 1
            continue
        idx = r_offset - tbase
        insn = struct.unpack_from(">I", tdata, idx)[0]
        calls.append((r_offset, "bl" if (insn & 1) else "b") + entry)

    # ---- reports ----
    per_import = defaultdict(list)
    for caller, _kind, module, name, stub in calls:
        per_import[(module, name, stub)].append(caller)

    def write(path, header, rows):
        with io.open(path, "w", encoding="ascii", newline="\n") as f:
            f.write(header + "\n")
            for row in rows:
                f.write("\t".join(row) + "\n")

    summary = [(str(len(addrs)), module, name, f"{stub:08x}")
               for (module, name, stub), addrs in
               sorted(per_import.items(), key=lambda kv: (-len(kv[1]), kv[0][1]))]
    write(os.path.join(OUT_DIR, "imports_by_name.tsv"), "calls\tmodule\tname\tstub", summary)

    detail = [(f"{c:08x}", kind, module, name, f"{stub:08x}")
              for c, kind, module, name, stub in sorted(calls)]
    write(os.path.join(OUT_DIR, "import_calls.tsv"), "caller\tkind\tmodule\tname\tstub", detail)

    unused = [k for k in imports.values() if (k[0], k[1], k[2]) not in per_import]
    print(f"call sites: {len(calls)} "
          f"({sum(1 for c in calls if c[1] == 'bl')} bl, "
          f"{sum(1 for c in calls if c[1] == 'b')} b)")
    print(f"imports called at least once: {len(per_import)} / {len(imports)}")
    print(f"imports never called directly: {len(unused)}")
    print(f"imports whose address is taken (lis/addi): {len(taken)}")
    if stray:
        print(f"unexpected reloc types to imports: {dict(stray)}")
    print("top 12:")
    for row in summary[:12]:
        print(f"  {int(row[0]):5d}  {row[1]:12s} {row[2]}")
    if unused:
        print("never called:", ", ".join(sorted(f"{m}/{n}" for m, n, _ in unused))[:800])


if __name__ == "__main__":
    main()
