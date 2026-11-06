# Near-miss archive

These candidates were decompiled but are **not byte-identical** to
`Block.elf`, so they are not in `src/functions.tsv` and are not claims of a
match. They are kept as reference: a later source-shape change may turn one
into a match. `tools/match.py` ignores this directory.

`func_XXXXXXXX.c` files are raw m2c output, including its macro preamble; the
older `fn_*.c` files are hand-written candidates. Some do not compile; that is
part of the record. Regenerate a candidate or fix its source shape rather than
treating an archived file as verified code.

The 144 open `0x0250` candidates are archived in
[`0250/`](0250/README.md); that directory has its own manifest.

## `0x028`-`0x029` bands

The twenty-first, twenty-second, twenty-fourth, twenty-fifth and twenty-sixth passes added twenty-three band
archives. Each chunk directory has its own README with the full candidate
table.

| Band | Leaf | Non-leaf | Total |
|---|---:|---:|---:|
| [`02800000_02820000`](02800000_02820000/) | 7 | 98 | 105 |
| [`02820000_02824000`](02820000_02824000/) | 0 | 4 | 4 |
| [`02824000_02828000`](02824000_02828000/) | 6 | 54 | 60 |
| [`02828000_0282C000`](02828000_0282C000/) | 1 | 22 | 23 |
| [`0282C000_02830000`](0282C000_02830000/) | 5 | 20 | 25 |
| [`02830000_02834000`](02830000_02834000/) | 2 | 17 | 19 |
| [`02834000_02838000`](02834000_02838000/) | 0 | 14 | 14 |
| [`02838000_0283C000`](02838000_0283C000/) | 1 | 28 | 29 |
| [`0283C000_02840000`](0283C000_02840000/) | 3 | 15 | 18 |
| [`02840000_02844000`](02840000_02844000/) | 2 | 28 | 30 |
| [`02844000_02848000`](02844000_02848000/) | 1 | 25 | 26 |
| [`02848000_0284C000`](02848000_0284C000/) | 9 | 30 | 39 |
| [`0284C000_02850000`](0284C000_02850000/) | 2 | 15 | 17 |
| [`02850000_02854000`](02850000_02854000/) | 1 | 33 | 34 |
| [`02854000_02858000`](02854000_02858000/) | 5 | 28 | 33 |

The twenty-fifth pass added four 256 KB shard archives:

| Band | Candidates |
|---|---:|
| [`02858000_02898000`](02858000_02898000/) | 212 |
| [`02898000_028D8000`](02898000_028D8000/) | 270 |
| [`028D8000_02918000`](028D8000_02918000/) | 198 |
| [`02918000_02958000`](02918000_02958000/) | 133 |
| **Total** | **813** |

The twenty-sixth pass added four contiguous shard archives covering the next
512 KB:

| Band | Candidates |
|---|---:|
| [`02958000_02980C54`](02958000_02980C54/) | 121 |
| [`02980C54_029AD558`](02980C54_029AD558/) | 125 |
| [`029AD558_029C5334`](029AD558_029C5334/) | 122 |
| [`029C5334_029D8000`](029C5334_029D8000/) | 119 |
| **Total** | **487** |

Those passes added 173 and 138 candidates respectively. Fourteen close
call-bearing candidates were repaired and promoted to `src/functions.tsv`, and
the twenty-fourth pass added 179 more; the twenty-fifth pass added 813 and the twenty-sixth added 505. The
pass-26 recovery then promoted fifteen candidates, taking the archive to 2,005 archived candidates.

| File | Range | Status | Words | First diff |
|---|---|---|---|---|
| `fn_020250EC.c` | `020250EC..02025118` | near miss | 10/12 | -- |
| `fn_02025B78.c` | `02025B78..02025B90` | near miss | 2/7 | -- |
| `fn_02025E2C.c` | `02025E2C..02025E48` | near miss | 6/8 | -- |
| `fn_02025F6C.c` | `02025F6C..02025F7C` | near miss | 3/5 | -- |
| `fn_020312D0.c` | `020312D0..02031304` | near miss | 2/14 | -- |
| `fn_02031308.c` | `02031308..0203133C` | near miss | 2/14 | -- |
| `func_020909C4.c` | `020909C4..020909D0` | diff | 2/2 | -- |
| `func_02090F38.c` | `02090F38..02090F68` | diff | 9/13 | +0x0 |
| `func_02091B8C.c` | `02091B8C..02091BC4` | diff | 5/15 | +0x0 |
| `func_0209358C.c` | `0209358C..020935BC` | diff | 4/13 | +0x8 |
| `func_020943A4.c` | `020943A4..020943BC` | diff | 3/7 | +0x0 |
| `func_0209BA28.c` | `0209BA28..0209BA5C` | diff | 0/14 | +0x0 |
| `func_0209F468.c` | `0209F468..0209F470` | diff | 2/3 | +0x0 |
| `func_020A35F0.c` | `020A35F0..020A3618` | diff | 6/11 | +0x0 |
| `func_020A37E0.c` | `020A37E0..020A37E8` | diff | 2/3 | +0x0 |
| `func_020A56B4.c` | `020A56B4..020A56D4` | compile failure | -- | -- |
| `func_020A5780.c` | `020A5780..020A579C` | diff | 1/8 | +0x4 |
| `func_020A6470.c` | `020A6470..020A649C` | diff | 6/12 | +0x0 |
| `func_020A6754.c` | `020A6754..020A677C` | compile failure | -- | -- |
| `func_020A6944.c` | `020A6944..020A6964` | diff | 1/8 | +0x0 |
| `func_020AE694.c` | `020AE694..020AE6AC` | diff | 6/7 | +0x10 |
| `func_020AE6B0.c` | `020AE6B0..020AE6C8` | diff | 6/7 | +0x10 |
| `func_020B45A4.c` | `020B45A4..020B45D8` | diff | 8/14 | +0x0 |
| `func_020B51B4.c` | `020B51B4..020B51CC` | diff | 3/7 | +0x8 |
| `func_020B6D3C.c` | `020B6D3C..020B6D68` | diff | 2/12 | +0x0 |
| `func_020B6D6C.c` | `020B6D6C..020B6D94` | compile failure | -- | -- |
| `func_020B7014.c` | `020B7014..020B7040` | diff | 2/11 | +0x4 |
| `func_020BBF98.c` | `020BBF98..020BBFC0` | diff | 1/10 | +0x0 |
| `func_020BC480.c` | `020BC480..020BC4B0` | diff | 1/13 | +0x0 |
| `func_020BC550.c` | `020BC550..020BC580` | diff | 1/13 | +0x0 |
| `func_020BDEB8.c` | `020BDEB8..020BDEE0` | diff | 0/2 | +0x0 |
| `func_020DA4B4.c` | `020DA4B4..020DA4CC` | diff | 2/7 | +0x0 |
| `func_020EC218.c` | `020EC218..020EC250` | diff | 7/15 | +0x0 |
| `func_020F41B8.c` | `020F41B8..020F41FC` | diff | 5/18 | +0x8 |
| `func_020F4278.c` | `020F4278..020F42A4` | diff | 7/12 | +0x0 |
| `func_020F4868.c` | `020F4868..020F4894` | diff | 7/12 | +0x0 |
| `func_020F48D0.c` | `020F48D0..020F4904` | diff | 6/14 | +0x0 |
| `func_020F6E74.c` | `020F6E74..020F6EA8` | compile failure | -- | -- |
| `func_020F9C04.c` | `020F9C04..020F9C28` | diff | 4/10 | +0x0 |
| `func_020F9C84.c` | `020F9C84..020F9CA8` | diff | 4/10 | +0x8 |
| `func_020F9FB0.c` | `020F9FB0..020F9FDC` | diff | 1/11 | +0x4 |
| `func_020F9FE0.c` | `020F9FE0..020FA00C` | diff | 1/11 | +0x4 |
| `func_020FA060.c` | `020FA060..020FA08C` | diff | 1/11 | +0x4 |
| `func_020FA0E0.c` | `020FA0E0..020FA10C` | diff | 1/11 | +0x4 |
| `func_020FA518.c` | `020FA518..020FA544` | diff | 1/11 | +0x4 |
| `func_020FA594.c` | `020FA594..020FA5C0` | diff | 1/11 | +0x4 |
| `func_020FA650.c` | `020FA650..020FA67C` | diff | 1/11 | +0x4 |
| `func_02100658.c` | `02100658..0210068C` | diff | 0/2 | +0x0 |
| `func_021012AC.c` | `021012AC..021012B8` | diff | 2/4 | +0x4 |
| `func_02102044.c` | `02102044..02102070` | diff | 1/11 | +0x4 |
| `func_02102248.c` | `02102248..02102274` | diff | 1/11 | +0x4 |
| `func_021024DC.c` | `021024DC..02102508` | diff | 1/11 | +0x4 |
| `func_02103470.c` | `02103470..021034A0` | diff | 7/13 | +0xC |
| `func_021037CC.c` | `021037CC..021037FC` | diff | 1/13 | +0x0 |
| `func_021078F0.c` | `021078F0..0210791C` | diff | 1/11 | +0x4 |
| `func_02113C98.c` | `02113C98..02113CC4` | diff | 5/12 | +0x4 |
| `func_02114550.c` | `02114550..02114574` | diff | 5/10 | +0x0 |
| `func_021178EC.c` | `021178EC..0211790C` | diff | 1/7 | +0x4 |
| `func_02119B48.c` | `02119B48..02119B70` | diff | 8/11 | +0x10 |
| `func_02122988.c` | `02122988..021229A8` | diff | 1/9 | +0x0 |
| `func_02122E24.c` | `02122E24..02122E64` | compile failure | -- | -- |
| `func_02132CC8.c` | `02132CC8..02132D0C` | diff | 2/18 | +0x0 |
| `func_02132D10.c` | `02132D10..02132D30` | compile failure | -- | -- |
| `func_021349A0.c` | `021349A0..021349C4` | compile failure | -- | -- |
| `func_02134A8C.c` | `02134A8C..02134AA8` | compile failure | -- | -- |
| `func_02134AAC.c` | `02134AAC..02134AC4` | diff | 6/7 | +0xC |
| `func_02137CFC.c` | `02137CFC..02137D1C` | diff | 1/9 | +0x0 |
| `func_02137F9C.c` | `02137F9C..02137FCC` | diff | 3/12 | +0x8 |
| `func_02140AB8.c` | `02140AB8..02140AE8` | diff | 7/13 | +0xC |
| `func_02141E24.c` | `02141E24..02141E44` | diff | 1/9 | +0x0 |
| `func_0214415C.c` | `0214415C..02144180` | diff | 0/9 | +0x0 |
| `func_02149874.c` | `02149874..02149898` | diff | 0/9 | +0x0 |
| `func_0214C7DC.c` | `0214C7DC..0214C7FC` | diff | 6/9 | +0x4 |
| `func_02158790.c` | `02158790..021587BC` | diff | 8/12 | +0x0 |
| `func_02172174.c` | `02172174..02172190` | diff | 1/7 | +0x4 |
| `func_02172B70.c` | `02172B70..02172B90` | diff | 3/9 | +0x0 |
| `func_02172CB4.c` | `02172CB4..02172CCC` | diff | 1/6 | +0x4 |
| `func_02172CD0.c` | `02172CD0..02172CE8` | diff | 1/6 | +0x4 |
| `func_02172E6C.c` | `02172E6C..02172E84` | diff | 1/6 | +0x4 |
| `func_021762AC.c` | `021762AC..021762BC` | diff | 0/4 | +0x0 |
| `func_02184948.c` | `02184948..0218498C` | diff | 14/18 | +0x0 |
| `func_0218A10C.c` | `0218A10C..0218A140` | diff | 11/14 | +0x0 |
| `func_0218FEBC.c` | `0218FEBC..0218FEFC` | compile failure | -- | -- |
| `fn___init.c` | `02B8AE48..02B8AEC8` | near miss | -- | -- |
| `fn_025081C4.c` | `025081C4..02508224` | near miss | 17/25 | +0x20 |

The archive began with the fifth through seventh passes and now includes the
sixteenth-pass indirect selector and the `0x028` sweeps; see
`docs/DECOMPILATION.md` for the surrounding batches.
