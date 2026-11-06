# Reconstructed source

> **GitHub file-list limit:** this directory has more than 1,000 entries, so
> GitHub omits `near/` and `functions.tsv` from the file listing. Both are
> tracked: [near-miss archive](near/README.md) and
> [functions.tsv](functions.tsv).

One function per file. `functions.tsv` maps each file to its address range;
the optional fifth field holds full compiler flags for that row. The size is
what `tools/match.py` verifies.

`config/function_names.tsv` proposes display aliases and `config/function_groups.tsv`
proposes source groups. Both are evidence metadata: neither renames the symbol
in `functions.tsv` or changes what the matcher verifies. See
`docs/HUMAN_READABLE.md` before applying either.

| Function | Range | Size | What it is |
|---|---|---|---|
| `func_02010A14` | `0x02010A14..0x02010A20` | 16 B | 32-bit null test at +0x168 |
| `func_020117FC` | `0x020117FC..0x02011808` | 16 B | `(field - 29) + arg` |
| `func_02015FCC` | `0x02015FCC..0x02015FF0` | 40 B | `u8` OR of two flag bytes |
| `func_020163DC` | `0x020163DC..0x020163F0` | 24 B | clear two child flags |
| `func_02017320` | `0x02017320..0x0201734C` | 48 B | early-return flag combiner |
| `func_020180E8` | `0x020180E8..0x020180F4` | 16 B | 32-bit null test at +0x1E8 |
| `func_0201AA84` | `0x0201AA84..0x0201AA94` | 20 B | enum equality, +0x1E8 == 2 |
| `func_02020410` | `0x02020410..0x02020438` | 44 B | bounded vector append |
| `func_02021C48` | `0x02021C48..0x02021C58` | 20 B | enum equality, +0x178 == 3 |
| `func_02022860` | `0x02022860..0x02022870` | 20 B | enum equality, +0x180 == 4 |
| `func_02022874` | `0x02022874..0x02022884` | 20 B | enum equality, +0x180 == 5 |
| `func_02023C64` | `0x02023C64..0x02023C70` | 16 B | 32-bit null test at +0x180 |
| `func_02023DC0` | `0x02023DC0..0x02023DD4` | 24 B | float `>` predicate |
| `func_02023DD8` | `0x02023DD8..0x02023DF8` | 36 B | two float2 copies |
| `func_02025B94` | `0x02025B94..0x02025BA0` | 16 B | 32-bit null test at +0x0C |
| `func_0202655C` | `0x0202655C..0x0202658C` | 52 B | six-float copy |
| `func_02029ADC` | `0x02029ADC..0x02029B00` | 40 B | zero-field or flag predicate |
| `func_0202C748` | `0x0202C748..0x0202C754` | 16 B | 32-bit null test at +0x178 |
| `func_0202C758` | `0x0202C758..0x0202C774` | 32 B | unsigned range 12..14 |
| `func_0202EBDC` | `0x0202EBDC..0x0202EBEC` | 20 B | enum equality, +0x178 == 3 |
| `func_0202EBF0` | `0x0202EBF0..0x0202EC00` | 20 B | enum equality, +0x178 == 1 |
| `func_02030854` | `0x02030854..0x02030860` | 16 B | zero test at +0x178 |
| `func_02031278` | `0x02031278..0x020312A0` | 44 B | bounded append at +0x44 |
| `func_020312A4` | `0x020312A4..0x020312CC` | 44 B | bounded append at +0x50 |
| `func_02031724` | `0x02031724..0x02031730` | 16 B | zero test at +0x0C |
| `func_02035890` | `0x02035890..0x0203589C` | 16 B | store +0xBC, set flag +0xCA |
| `func_020358A0` | `0x020358A0..0x020358AC` | 16 B | zero test at +0x0C |
| `func_02035914` | `0x02035914..0x02035938` | 40 B | clear two child flags |
| `func_0203593C` | `0x0203593C..0x02035950` | 24 B | set one child flag |
| `func_02035954` | `0x02035954..0x0203595C` | 12 B | set flag +0xCD |
| `func_020359B4` | `0x020359B4..0x020359EC` | 60 B | mirror count, then append |
| `runtime_init` | `0x02711500..0x0271154C` | 80 B | save loader args, call `__init`, call `main` |
| `startup_register` | `0x02BCF5D0..0x02BCF634` | 104 B | lock, callback, 36-slot registry |
| `func_02BCF5CC` | `0x02BCF5CC..0x02BCF5CC` | 4 B | tail thunk to `func_02BCF67C` |
| `func_02BCF688` | `0x02BCF688..0x02BCF6AC` | 40 B | link-insertion helper |

## Near-miss archive

[`near/`](near/README.md) holds the 2,023 candidates that decompiled but are
not byte-identical to `Block.elf`. They are not in `functions.tsv` and are
not claims of a match; `tools/match.py` ignores them.

These 35 representative rows are byte-identical to the retail build at
`-O2`; the full 1,623-row table is in `functions.tsv`. See
`../docs/DECOMPILATION.md` for the listings and the codegen traps.

These files are a derivative work. Read `../LICENSE-DECOMPILED` before reusing
anything here.
