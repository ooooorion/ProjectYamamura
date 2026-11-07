# Decompilation notes -- first through twenty-seventh passes (Stage 7)

Working notes for the decompilation and byte-match passes against
`Block.elf`. Every number here came from a command that was run; the exact
commands are at the bottom.

## Status

| | |
|---|---|
| Functions decompiled | 1,802 |
| Byte-identical to `Block.elf` | **1,802 of 1,802** |
| Compiler | GHS `ccppc` 5.3.27 (licensed locally; licence material is not included) |
| Harness | `tools/match.py` (table, applies object relocations), `tools/crack.py` (one candidate, with relocations) and `tools/batch.py` (an address band) |
| Sources | `src/fn_*.c`, table in `src/functions.tsv` |

The original four also match at `-O3` and `-Ospeed`; `-O1`, `-Ogeneral` and
`-Ospace` do not reproduce them. That difference is what identifies the build's
optimisation class.

## Toolchain

`ccppc` 5.3.27 is a licensed commercial compiler. Reproducing the byte checks
requires a local installation, but the compiler, its licence files, and its
licence-server configuration are not part of this repository. No licence,
serial, or host identifier is recorded here. The only toolchain details the
project depends on are the version and the per-row flags in
`src/functions.tsv`.

## How the functions were chosen

`main.s` has no symbols, so function starts are the targets of internal `bl`
instructions inside `.text` (`0x02000020..0x02C6E298`). That yields **27,267**
candidate starts.

A candidate was kept only if all of these held:

- its last instruction is `blr` (the next candidate start is the boundary);
- it is a leaf (no `bl` inside);
- every branch stays inside the range;
- it never touches `r2` (small-data area, which would need the data section);
- 6..16 instructions.

That leaves **1,529**. Four were taken from the front and checked by hand.

A second pass used the same start set with a wider 2..18 instruction window,
still leaf, still no `r2` and with every branch internal. That yields **3,166**
candidates. 23 were taken from the early `.text` band around the first matches
(`0x02010000..0x02030000`); 21 are byte-identical. The four that are not are
covered under "Near misses" below.

Only `runtime_init`, `startup_register` and the two adjacent helpers reference
external data or calls; the other 130 matches are leaves. Some leaves still
carry internal branch relocations, which the harness applies. `tools/match.py` now
parses each object's `.rela.text`, resolves symbols through
`config/symbols.txt`, and applies `R_PPC_ADDR16_HA`/`LO`, `R_PPC_ADDR32`,
`R_PPC_ADDR24`, `R_PPC_REL24`, `R_PPC_REL14` and `R_PPC_REL32` before the word
comparison. Unresolved relocations print `BLOCKED` and are never counted as
matches. Existing objects also carry internal branch relocations; applying
them leaves the other 31 matches intact.

## func_02015FCC -- 0x02015FCC..0x02015FF0, 10 instructions, 40 bytes

```
88030248  lbz     r0,584(r3)
2C000000  cmpwi   r0,0
39800001  li      r12,1
40820014  bne     0x02015FEC
88030249  lbz     r0,585(r3)
2C000000  cmpwi   r0,0
40820008  bne     0x02015FEC
39800000  li      r12,0
5583063E  clrlwi  r3,r12,24
4E800020  blr
```

```c
u8 func_02015FCC(Obj *self) {
    return self->flag_584 || self->flag_585;
}
```

The closing `clrlwi r3,r12,24` is an 8-bit truncation. That is the signature of
a `u8` return; `_Bool` produces a different normalisation (see trap 1).

## func_02023DC0 -- 0x02023DC0..0x02023DD4, 6 instructions, 24 bytes

```
C1A300FC  lfs     f13,252(r3)
C0030104  lfs     f0,260(r3)
FC0D0000  fcmpu   cr0,f13,f0
7C000026  mfcr    r0
540317FE  rlwinm  r3,r0,2,31,31
4E800020  blr
```

```c
b8 func_02023DC0(Obj *self) {
    return self->value_252 > self->value_260;
}
```

`SH=2` reads CR0[GT], which calibration confirms (trap 2). The predicate is
greater-than, not equality: the mask, not intuition, decides. Both `u8` and
`b8` return types reproduce this function exactly.

## func_0202655C -- 0x0202655C..0x0202658C, 13 instructions, 52 bytes

```
C0040000  lfs     f0,0(r4)
D0030044  stfs    f0,68(r3)
C0040004  lfs     f0,4(r4)
D0030048  stfs    f0,72(r3)
...
D0030058  stfs    f0,88(r3)
4E800020  blr
```

```c
void func_0202655C(Dst *self, Src *src) {
    self->x = src->a[0];
    ...
    self->v = src->a[5];
}
```

Six floats, source `+0x00..+0x14`, destination `+0x44..+0x58`. No branches, no
calls. This one matches at every optimisation level tried, including `-Ospace`.

## func_02017320 -- 0x02017320..0x0201734C, 12 instructions, 48 bytes

```
8803024A  lbz     r0,586(r3)
39800000  li      r12,0
2C000000  cmpwi   r0,0
88030249  lbz     r0,585(r3)
41820008  beq     0x02017338
39800001  li      r12,1
2C000000  cmpwi   r0,0
38000004  li      r0,4
41820008  beq     0x02017348
38000002  li      r0,2
7D830378  or      r3,r12,r0
4E800020  blr
```

```c
u32 func_02017320(Obj *self) {
    u32 result = 0;
    if (self->flag_24A) result |= 1;
    if (self->flag_249) return result | 2;
    return result | 4;
}
```

The early-return form is what reproduces the target. The obvious ternary
`(f24A ? 1 : 0) | (f249 ? 2 : 4)` means the same thing and compiles to 40 bytes
(see trap 3).

## Second pass -- 17 more matches

The second pass stayed in one address band so the functions share a probable
object model. It adds these ranges, all verified at `-O2`:

```
02010A14  020117FC  020163DC  020180E8  0201AA84  02020410
02021C48  02022860  02022874  02023C64  02023DD8  02025B94
02029ADC  0202C748  0202C758  0202EBDC  0202EBF0
```

The shapes repeat, which is what makes a batch worthwhile:

- **null tests** at `+0x168`, `+0x1E8`, `+0x180`, `+0x0C` and `+0x178`:
  `lwz` + `cntlzw` + `srwi 5`, returning `u32`;
- **enum equality** against 1, 2, 3, 4 and 5: `xori` + `cntlzw` + `srwi 5`,
  returning `u32`;
- **small copies** (`02023DD8`, two float2s) and **bounded append**
  (`02020410`, count/capacity/items at +0x00/+0x04/+0x08);
- **predicates** (`02029ADC`, `0202C758`) where the return is `u8`, so the
  result is materialised as 1/0 and truncated with `clrlwi`.

Five source-shape lessons came out of the first two batches:

1. The bounds compare in `02020410` is `cmpw`, not `cmplw`: count and capacity
   are `s32`. Changing the field types was the whole fix.
2. In `0202C758`, `u8 result` made GHS branch straight to `blr` and produce
   28 bytes. `u32 result` with `return (u8)result;` keeps the single exit and
   the target's 32 bytes.
3. In `020163DC`, reusing one local `Child *` prevents the second pointer load
   from being hoisted; spelling both dereferences inline produces r10/r12
   instead of the target's r12/r11.
4. `~field != 0` and `field != 0xFFFFFFFF` are the same predicate but compile
   differently (`not` versus `li`+`xor`), and even the same `not` form lands in
   a different register under the two spellings.
5. `02029ADC` is a disjunction, not a conjunction. The target's `beq` keeps the
   default 1 when `field_376 == 0`, so the predicate is
   `field == 0 || flag != 0`; the negation compiles to the same size but the
   wrong control flow.

## Third pass -- 10 more matches

The third pass tested `tools/crack.py` on 12 eligible leaves in
`0x02030000..0x02050000`:

```
02030854  02031278  020312A4  02031724  02035890
020358A0  02035914  0203593C  02035954  020359B4
```

Ten are byte-identical at `-O2`. Seven matched directly from m2c's output.
The two vector appends (`02031278`, `020312A4`) needed the
count/capacity/items struct, and `020359B4` needed a local array pointer to
reproduce the target's `r12` count / `r11` base allocation. `02035914` also
matched from m2c, but its first clean rewrite used a typed `Child *` and did
not; `void *` children restore the target's zero-store schedule.

The batch also exposed an m2c valid-syntax bug: indexed fields were emitted as
`*((i * 4) + M2C_FIELD(...))`, which is not valid C. `tools/crack.py` folds
the index into the byte offset before compiling; the five candidates that hit
it then built.

The SDK's `system/include/types.h` confirms the GHS scalar block used by
`include/block.h` (`s8`/`s16`/`s32`/`s64`, `u8`/`u16`/`u32`/`u64`) and maps
`__cntlzw` to `__CLZ32`, consistent with the `cntlzw` null tests.

## Fourth pass -- 31 more matches from 44 candidates

The fourth pass pointed `tools/batch.py` at `0x02050000..0x02090000`, a fresh
band of 44 eligible leaves. The driver slices each candidate, runs m2c in
valid-syntax mode, compiles it with GHS at `-O2`, applies the object's
relocations and compares every word, logging one row per candidate to
`build/batch/results.tsv`.

Thirty-one were exact, all on m2c's first output; the work was turning
`M2C_FIELD` accesses into structs and re-verifying, not fixing code. One
rewrite initially put `0208E3B8`'s fields at +0x00/+0x04 instead of
+0x20/+0x24, and the harness caught it on the next table run. That is the
intended division of labour: m2c proposes, the byte comparison decides.

The batch also produced a useful failure taxonomy: eleven near misses (ten of
them register-allocation only, one an element-size mismatch), one loop-shape
failure that m2c could not compile, and one alignment artefact. They are
listed under "Near misses".

## Fifth pass -- 25 more matches from 50 candidates

The next band, `0x02090000..0x020D0000`, produced 50 eligible leaves: 25
exact, 22 differences and 3 compile failures. Most of the matches were again
direct m2c output. One clean rewrite (`02091978`) changed only the declaration
order of two float locals; declaring `limit` before `value` put the result in
`f0`, as the target does, instead of `f13`.

Every non-match from this pass -- and the earlier near misses -- is archived
in `src/near/`, with ranges and word counts in `src/near/README.md`. The
archive is reference material, not a claim: `tools/match.py` still reads only
`src/functions.tsv`.

## Sixth pass -- 32 more matches and a section break

Two bands followed: `0x020D0000..0x02110000` and
`0x02110000..0x02150000`. Each had 37 eligible leaves. The first produced 13
exact, 23 differences and 1 compile failure; the second produced 19 exact, 14
differences and 4 compile failures. The pass total is 32 of 74 exact.

The first band is not one uniform region. From `0x020D0000` to `0x020FD9C8`
(`0x2D9C8` bytes) there are 17 eligible leaves and only one exact
(`020DCD94`); the functions are larger and their register allocation usually
differs on m2c's first output. At `0x020FD9C8` a compact accessor block
starts: twelve functions in `0xB9C` bytes (`0x020FD9C8..0x020FE564`), all
twelve exact, every one 8 to 36 bytes. It holds a constant return, a
four-float copy, a mask test and nine float getters built from child fields
at +0xB8/+0xBC/+0x30C and object fields at +0x88..+0x94. That is a sharp,
local change in code shape, but it is an island: the next eight candidates,
from `0x02100658` to `0x021078F0`, are all differences.

The section break is at `0x02140000`. Counting `bl` targets in 64 KB buckets,
the region rises from 137 starts at `0x020F0000` to 229 at `0x02120000`,
falls to 151 at `0x02130000`, then to 41 at `0x02140000` and 27 at
`0x02150000`. That 73% drop is sustained, not one oversized function. The
last candidates of the band cross the break (`02140AB8`, `02141E24`,
`0214415C`, `021445D8`, `02146950`, `02149874`, `0214C7DC`) and stop before
`0x02150000`; the next band should start there rather than assume the dense
shapes continue. The table then had 123 functions, 2,704 bytes, 0.45% of the
27,267 starts.

The 32 new matches are all leaves; the harness applies their internal branch
relocations.

### Near misses

Six from the second pass were decompiled but are not byte-identical, so they
are not in `src/` or `src/functions.tsv`:

| Range | Bytes | Target vs object | Words |
|---|---|---|---|
| `02025E2C..02025E48` | 32 | `slwi r0,r4,3` vs `slwi r11,r4,3` | 6/8 |
| `02025F6C..02025F7C` | 20 | `lwz r0` + `not r12,r0` vs `lwz r12` + `not r12,r12` | 3/5 |
| `020250EC..02025118` | 48 | `lbz r10` vs `lbz r0` for the flags byte | 10/12 |
| `02025B78..02025B90` | 28 | `li r11,1` vs `li r12,1` | 2/7 |
| `020312D0..02031304` | 56 | target `mr r12,r3` + `li r3,0` before `cmplw`; object differs in load/zero order | 2/14 |
| `02031308..0203133C` | 56 | same getter shape at +0x70 | 2/14 |

All six have clear semantics, and all six differ only in scratch-register
choice. Local variables, pointer casts, 8-byte record types, signed indices,
`_Bool`/`volatile` variants and a full `-O` sweep were tried; none moved the
target's register. That points at a compiler/flag difference in register
allocation rather than a misread function, but it is not a match and is not
claimed as one.

Twelve more from the fourth pass were decompiled but are not byte-identical:

| Range | Bytes | Target vs object | Words |
|---|---|---|---|
| `0205D1E8..0205D220` | 60 | target spills the args at +0x0C/+0x08; object writes +0x04 first | 1/7 |
| `0206E4D4..0206E50C` | 56 | m2c loop shape; target uses `stfsu`/`bdnz`, candidate a do-while counter | 3/14 |
| `0207CDC0..0207CDE4` | 40 | `lwz r11` + `cmpw r11` vs `lwz r12` + `cmpw r12` | 1/8 |
| `0207FA18..0207FA40` | 44 | target `lwz r11`/`lwz r10`; object `lwz r12`/`lwz r11` | 1/11 |
| `020853F4..02085434` | 68 | divide-by-9 loop, target temporaries in r9/r11, object r8/r11 | 4/17 |
| `02088058..02088088` | 52 | target forms the field address in r11; object uses r12 then r11 | 3/13 |
| `020882C0..020882F0` | 52 | target `li r12,1` + `clrlwi`; object `li r0,1` + `or` | 7/13 |
| `02089B98..02089BA8` | 20 | target keeps the child in r11; object uses r12 | 3/5 |
| `0208D7E4..0208D828` | 72 | target loads f13 then f12; object f12 then f13 | 10/18 |
| `0208D994..0208D9C4` | 52 | target f13/r12; object f0/r11 | 8/13 |
| `0208D9C8..0208D9F8` | 52 | same float pair at +0xBC/+0x04 | 8/13 |
| `0208FFF4..02090014` | 36 | target scales the index by 4 (`rlwinm ...,2,...`); object by 16 | 8/9 |

`0206E4D4` does not compile as generated: m2c writes `void *` arithmetic
(`var_r8 += 0xC`). Fixing the type makes it build but the loop is still
wrong, so it stays a source-shape failure. A thirteenth candidate,
`0207E560..0207E584` (36 bytes), is alignment padding: nine consecutive
`blr` instructions with no prologue or body. `tools/batch.py` now rejects an
all-`blr` run longer than one instruction.

The fifth, sixth and seventh passes archived 77 non-matches under `src/near/`
(25 from the fifth, 42 from the sixth, 10 from the seventh) rather than
tabulating them here.

The first relocation-bearing candidate is a separate near miss. `__init`
(`0x02B8AE48..0x02B8AEC8`, 132 bytes, 33 instructions) has the right
guard/table-walk semantics and its six `ADDR16_HA/LO` relocations resolve, but
the generated code does not match: the straightforward source is 100 bytes at
`-O2` (pointer walk), 120 bytes at `-O1` and 124 bytes at `-O1 -Onocse`. The
target keeps the index in `r31`, reloads `__init_array[i]` for the call, and
reloads the table base after `bctrl`; the candidates either fold the load or
choose a different saved register. It is kept out of `src/` and
`src/functions.tsv`.

## Seventh pass -- 11 matches in a large-method region

The 320 KB from `0x02140000` to `0x02190000` is a different code regime
from the preceding 320 KB (`0x020F0000..0x02140000`). The function count
falls from 820 to 289 while the code size stays the same. Mean extent rises
from 400 to 1,127 bytes and median extent from 136 to 324 bytes; calls per
function rise from 4.8 to 11.4 and indirect dispatch from 0.49 to 0.99 per
function. The region is not uniformly sparse: `0x02160000` and `0x02170000`
still hold 72 and 109 starts. What changes is the mix -- from many short
accessors to fewer 0.3-1.1 KB methods that save FPRs/GPRs, run loops, dispatch
through `bctrl`, and use paired-single/vector instructions.

The boundary is not an ELF section or even a function boundary. `.text` is
one section, and the function at `0x0214FAB0` runs to `0x02151918`, crossing
`0x02150000`; the first start after the boundary is `0x0215191C`. That
7,788-byte function is far outside the leaf filter and was not a candidate.

The band `0x02150000..0x02190000` has 248 starts but only 21 eligible leaves
(8.5%). The first batch pass was 9 exact, 9 differences and 3 compile
failures. Two compile failures were m2c type/pointer-arithmetic errors:
`021703EC` and `02170410` are the paired strided float copies, and typed
`f32 *` sources take both to exact. That makes 11 matches from 21 candidates.
The third compile failure (`0218FEBC`) still differs after repairing its
`void *` cast; the ten remaining non-matches are archived. The new matches
are all leaves; four carry internal branch relocations. The eleven are
`0215F510`, `02164AD0`, `0216C4A4`, `021703EC`, `02170410`, `02172BFC`,
`02172CEC`, `02173C78`, `021756A0`, `02177E50` and `02187690`. The table
then stood at 134 functions, 3,076 bytes, 0.49% of the 27,267 starts.

## Eighth pass -- 11 call-bearing matches

The seventh pass left most of the large-method region untested because the
batch loop rejected every function containing a call. The matcher already
applied `REL24`; the gap was in discovery and in `crack.py`'s raw compare.
`tools/batch.py --allow-calls` now accepts direct `bl` calls, rejects `bla`,
`bcl`, external branches and r2-relative access, and applies the object's
relocations before comparison. `tools/crack.py` now applies the same
relocations, so it no longer reports `bl 0x0` placeholders as differences.

A reloc-aware sweep of 96 candidates in `0x02140000..0x02190000` produced 22
exact: 11 already-registered matches and 11 call-bearing functions. The new
matches are `021530B8`, `02162088`, `02170888`, `02172134`, `02177CF0`,
`0217877C`, `021799CC`, `0217DA20`, `0217DA70`, `0217DACC` and `0217F454`.
They call helpers, four invoke vtable slot 5, and 35 object relocations were
applied across them. The table is now 145 functions, 3,980 bytes, 0.53% of
the 27,267 starts.

## Ninth pass -- 22 non-leaf matches in the next 448 KB

The call-aware sweep continued through `0x02190000..0x02200000`. The window
has 656 starts, mean measured extent 698 bytes and median 204; 599 bodies end
in `blr`, and 297 pass the 60-instruction cap. It is denser than the preceding
large-method band, so it was run as seven 64 KB blocks.

The sweep found 48 exact functions: 22 call-bearing and 26 leaves. The 22
call-bearing matches are registered here; the leaves are left for a leaf pass.
They cover vtable teardown and dispatch, small lifecycle wrappers, three
`+0x4E8` release variants, and the switch-based state mapper `021F2B94`.
77 object relocations were applied across them. The table is now 167
functions, 5,828 bytes, 0.61% of the 27,267 starts.

The registered functions are `02197358`, `021A5C5C`, `021AB564`, `021AB5A8`,
`021B571C`, `021B5774`, `021C7C18`, `021C8F60`, `021C9054`, `021C90C0`,
`021D63B0`, `021D832C`, `021DA714`, `021DA768`, `021DA87C`, `021E8148`,
`021F2B94`, `021F6BB8`, `021FBEB4`, `021FD03C`, `021FDCD0` and `021FF258`.

## Tenth pass -- 47 non-leaf matches in the next 512 KB

The call-aware sweep moved through `0x02200000..0x02280000` in eight 64 KB
blocks. It tried 268 candidates and produced 48 exact functions: 47
call-bearing and one 8-byte leaf. The 47 call-bearing matches are registered;
the leaf (`02231B8C`) is left for a leaf pass. The remaining candidates were
134 diffs, 76 compile failures and 10 blocked local-constant relocations.

Most of the new matches are vtable lifecycle wrappers, flag-clearing cleanup
paths, and small direct dispatch helpers. The rest include two counter
rebuilds, an allocator wrapper and a vtable value setter. The table is now 214
functions, 10,572 bytes, 0.78% of the 27,267 starts. The registered functions
are listed under the tenth-pass marker in `src/functions.tsv`.

The compile failures are the same m2c/GHS type classes as the ninth pass;
candidate-only repairs did not produce a byte match.

## Leaf pass -- 27 exact leaves from 0x02190000..0x02280000

The ninth and tenth passes left 27 exact leaves unregistered. All 27 were
cleaned into the one-function-per-file source shape and verified against the
retail ranges. The table reached 241 functions, 11,052 bytes, 0.88% of the
27,267 starts.

## Eleventh pass -- 34 matches in the next 512 KB

The call-aware sweep continued through `0x02280000..0x02300000` in eight
64 KB blocks. All 34 exact functions were registered: 21 call-bearing and 13
leaves. The table reached 275 functions, 13,448 bytes, 1.01% of the 27,267
starts.

## Twelfth pass -- 70 matches in the next 512 KB

The sweep covered `0x02300000..0x02380000` in eight 64 KB blocks. All 70 exact
functions were registered: 53 call-bearing and 17 leaves. The table is now 345
functions, 19,408 bytes, 1.27% of the 27,267 starts.

## Thirteenth pass -- 119 matches in the next 512 KB

The sweep covered `0x02380000..0x02400000` in eight 64 KB blocks. All 119
exact functions were registered: 47 call-bearing and 72 leaves. The table is
now 464 functions, 26,432 bytes, 1.70% of the 27,267 starts.

## Fourteenth pass -- 94 matches in the next 512 KB

The sweep covered `0x02400000..0x02480000` in eight 64 KB blocks. All 94 exact
functions were registered: 44 call-bearing, 44 leaves and six with data
relocations only. The table is now 558 functions, 32,028 bytes, 2.05% of the
27,267 starts.

## Fifteenth pass -- 161 matches in the next 512 KB

The sweep covered `0x02480000..0x02500000` in eight 64 KB blocks. All 161 exact
functions were registered: 48 call-bearing, 99 leaves and fourteen with data
relocations only. The eight blocks contributed 8, 13, 4, 19, 36, 43, 20 and 18
matches. The table is now 719 functions, 38,944 bytes, 2.64% of the 27,267
starts.

## Sixteenth pass -- 79 matches and the selector-family repair

The sweep covered `0x02500000..0x02580000` in eight 64 KB blocks. The blocks
contributed 37, 1, 11, 10, 2, 5, 8 and 5 exact functions. The first block's 37
include 19 recovered by repairing a repeated m2c decode. In total the pass
registered 79 functions and 5,232 bytes. The table is now 798 functions,
44,176 bytes, 2.93% of the 27,267 starts.

### The selector-family decode

The selector family around `0x02508...` exposed two m2c failures at once. For
`02508228`, m2c emitted `func_025080DC(&sp8, arg1)` even though the helper takes
`self` first, and read the field at `+0x98` as
`M2C_FIELD(arg0, s32 *, 0x98 + (sp8 * 4))`. The callee's prologue consumes
`r3` as `self`; `+0x98` is a pointer to the entry array, not an inline array.
The corrected shape is:

```c
typedef struct {
    u8 pad0[0x90];
    u32 count;
    u8 pad94[4];
    s32 *items;
} Obj;

extern void func_025080DC(void *self, s32 *out, s32 arg);

void func_02508228(Obj *self, s32 arg1) {
    s32 index;
    s32 value;

    func_025080DC(self, &index, arg1);
    value = 0;
    if ((u32)index < self->count) value = self->items[index];
    func_02495078(value);
}
```

The 17 one-call selectors and the two extra-argument selectors reproduce this
shape word for word at `-O2` (22 instructions, 88 bytes). The same correction
recovers 19 functions that the raw batch had classed as `DIFF`.

The indirect sibling `025081C4` also loses the method's `this` argument. The
corrected source loads the selected object and calls
`(*(void (**)(void *))((u8 *)*(void **)object + 0x8C))(object)`. It reproduces
17 of 25 words; the first diff is `+0x20` and only scratch-register allocation
remains. It is archived under `src/near/`, not registered.

## runtime_init -- 0x02711500..0x0271154C, 20 instructions, 80 bytes

The first match with calls and data relocations. It saves the loader's two
arguments, executes the constructor table, publishes the arguments at
`0x10189810`/`0x10189814`, calls `main`, and returns zero:

```c
s32 runtime_init(s32 arg0, s32 arg1) {
    __init();
    runtime_arg0 = arg0;
    runtime_arg1 = arg1;
    main();
    return 0;
}
```

The object's four `ADDR16_HA/LO` data relocations and two `REL24` calls resolve
through `config/symbols.txt`; the result is 20/20 words at `-O2`.

## startup_register -- 0x02BCF5D0..0x02BCF634, 26 instructions, 104 bytes

This function takes the startup lock, publishes the callback at
`0x02C745E0`, and scans the 36-entry, 12-byte-slot table at `0x1034C000`.
The first free `+0x08` slot receives the argument, then `func_02BCF688` links
the slot and the lock is released. The `-Ospace` object uses
`_savesmall_16`/`_restsmall_16`, so the match needs those helper addresses in
`config/symbols.txt`:

```c
for (i = 0; i < 36; i++) {
    if (startup_table[i].field_8 == 0) {
        startup_table[i].field_8 = arg;
        func_02BCF688(&startup_table[i]);
        __ghsUnlock();
        return 0;
    }
}
__ghsUnlock();
return -1;
```

The source is `src/fn_startup_register.c`; the table row selects `-Ospace`.
The adjacent helpers also match: `func_02BCF5CC` is a four-byte tail thunk to
`func_02BCF67C`, and `func_02BCF688` is the 40-byte `-Ospace` lock-list
insertion helper.

## The match protocol

```
python tools/match.py                     # every row in src/functions.tsv
python tools/match.py func_02015FCC       # one function
python tools/match.py --sweep             # try common -O levels
```

For each row the harness compiles the source, finds the symbol in the object,
slices its `.text`, slices the same address range out of `Block.elf`, and
compares 32-bit words. An optional fifth field in `src/functions.tsv` holds
the full `ccppc` flags for that row; `--sweep` ignores it and tries the global
optimization levels instead. `MATCH` requires equal bytes *and* equal sizes; anything
else prints `n/total words`, the first differing offset, and both words in hex,
and makes the run exit non-zero. If compilation fails it stops with `BLOCKED`
and the compiler's own error.

For a new function, `tools/crack.py` wraps the mechanical half of the loop:

```
python tools/crack.py 02015FCC 02015FF0
python tools/crack.py --src src/fn_02015FCC.c
python tools/crack.py --src src/fn_02015FCC.c --sweep
```

It slices the range, runs m2c in valid-syntax mode, writes a compilable
candidate to `build/crack/`, compiles it with GHS, and prints a target/object
instruction diff. It reports `MATCH` only when bytes and size agree. It does
not infer struct fields: m2c's `M2C_FIELD` accesses are a first pass, and calls
or globals still need declarations. Use `--save src/fn_....c` only after the
candidate is understood; `--m2c-arg` passes an extra m2c flag such as
`--no-andor`.

## Results

Words matched out of the target's word count; `MATCH` also requires equal size.

| Function | Bytes | -O1 | -O2 | -O3 | -Ogeneral | -Ospeed | -Ospace |
|---|---|---|---|---|---|---|---|
| `func_02015FCC` | 40 | 9/10 | **10/10** | **10/10** | 9/10 | **10/10** | 3/10 |
| `func_02023DC0` | 24 | **6/6** | **6/6** | **6/6** | **6/6** | **6/6** | 2/6 |
| `func_0202655C` | 52 | **13/13** | **13/13** | **13/13** | **13/13** | **13/13** | **13/13** |
| `func_02017320` | 48 | 7/12 | **12/12** | **12/12** | 7/12 | **12/12** | 2/12 |

The speed-optimising family reproduces the image; the size-optimising and
debug-friendly levels do not. `-O2`, `-O3` and `-Ospeed` are indistinguishable
on this sample, so the build level is one of those three, not `-O1` and not
`-Ospace`.

The 130 later matches (17 in the second pass, 10 in the third, 31 in the
fourth, 25 in the fifth, 32 in the sixth, 11 in the seventh, plus
`runtime_init`, `startup_register`, `func_02BCF5CC` and `func_02BCF688`) all
report `MATCH`; the full sweep was not repeated for them after their shapes
were fixed.

## Three traps that cost the most time

### 1. The return type changes the code

`_Bool` (`b8`) makes GHS normalise a boolean with `addic`/`subfe`:

```
addic r12,r11,-1
subfe r3,r12,r11
```

The target instead truncates:

```
clrlwi r3,r12,24
```

That instruction is a `u8` return, not a `_Bool` one. Switching the return type
took `func_02015FCC` from 6/10 words and 44 bytes to an exact 40-byte match.

### 2. The CR mask names the comparison

`mfcr` + `rlwinm` implements a comparison-to-integer conversion, and the shift
amount identifies which CR bit is read. Compiling known expressions on this
compiler calibrates it:

| Source | Emitted conversion |
|---|---|
| `a > b` (int or float) | `rlwinm r3,r0,2,31,31` |
| `a == b` (float) | `rlwinm r3,r0,3,31,31` |

So `SH=2` is GT and `SH=3` is EQ. The function that looked like an equality test
was `>`. This is the one place where a wrong reading still compiles and looks
plausible; the calibration is worth keeping in mind for every predicate.

### 3. Equivalent C is not equivalent code

`func_02017320` returns `(f24A ? 1 : 0) | (f249 ? 2 : 4)`. Written as ternaries
it compiles to 40 bytes; written as an early-return `if` chain it compiles to
the target's 48 bytes, word for word. Both are correct C. Byte matching is
sensitive to source shape, not only to semantics.

## Seventeenth pass -- 76 exacts and the `0x0250` audit

The sweep covered `0x02580000..0x02600000` in eight 64 KB blocks. The blocks
contributed 5, 3, 6, 6, 19, 2, 31 and 4 exact functions. The three repaired
`0x0250E3` functions were registered with them: 79 rows and 4,836 bytes. The
table is now 877 functions, 49,012 bytes, 3.22% of the 27,267 starts, and all
877 rows pass `tools/match.py`.

The 166 `DIFF` rows from the preceding `0x0250` block are now audited in
[`NEAR_0250.md`](NEAR_0250.md). Twenty-two are recovered: the nineteen selector
entries and three `0250E3` functions. The remaining 144 are archived under
`src/near/0250/`; they split into 69
members of the `02508B6C` cluster, 58 using the `+0x78` indexed-field shape,
and 17 isolated rows. The two large families have source-shape fixes but remain
allocator-blocked; the report records their best candidate scores and first
differences.

## Eighteenth pass -- 144 exacts in the next 512 KB

The sweep covered `0x02600000..0x02680000` in eight 64 KB blocks. The blocks
contributed 24, 12, 8, 16, 31, 35, 13 and 5 exact functions, all registered:
144 rows and 5,160 bytes. The table is now 1,021 functions, 54,172 bytes, 3.74%
of the 27,267 starts; all 1,021 rows pass `tools/match.py`.

## Nineteenth pass -- 300 exacts in 1 MB

The sweep covered `0x02680000..0x02800000` in sixteen 64 KB blocks. The
blocks contributed 47, 7, 4, 23, 23, 15, 13, 7, 9, 5, 7, 11, 1, 72, 52 and 4 exact functions, all registered:
300 rows and 11,736 bytes. The table is now 1,321
functions, 65,908 bytes, 4.84% of the 27,267
starts; all 1,321 rows pass `tools/match.py`.

## Twentieth pass -- three exact leaves in `0x02800000..0x02820000`

A targeted ten-candidate leaf batch in the next untouched band found three
exact functions: `02811D44` (28 B), `02812FE4` (28 B) and `02815B54` (12 B).
All are `-O2` leaves and needed no source rewrite. The table is now 1,324
functions, 65,976 bytes, 4.86% of the 27,267 starts; all 1,324 rows pass
`tools/match.py`.

## Twenty-first pass -- 37 exacts through `0x02828000`

The call-aware sweep covered the rest of the first band and moved into two
further 16 KB bands. Nine batches ran: five non-leaf chunks through
`0x02800000..0x02820000`, then leaf and non-leaf batches for
`0x02820000..02824000` and `0x02824000..02828000`. They tried 203 candidates
and produced 37 exact functions -- 11 in the first band and 26 in the further
bands. The first band's non-leaf chunks contributed 0, 4, 5, 1 and 1 exact;
the further bands contributed 2 + 1 and 16 + 7.

All 37 were registered and the full table passes `tools/match.py`: 1,361
functions, 67,560 bytes, 4.99% of the 27,267 starts. The remaining 166
candidates from this sweep are archived under `src/near/`, alongside the
seven leaf misses from the preceding targeted batch; 173 new near sources
take the archive to 402.

## Twenty-second pass -- 24 exacts through `0x02840000`

Sixteen-kilobyte bands from `0x02828000` to `0x02840000` were swept in two
modes: leaf candidates at `-O2`, then call-bearing candidates with REL24
relocations applied. Twelve batches tried 162 candidates and produced 24 exact
functions in 740 bytes -- 17 leaves in 184 bytes and 7 call-bearing functions
in 556 bytes. Leaf success was strongest at `0x02838000..0x0283C000` (5 of 6)
and `0x0283C000..0x02840000` (5 of 8); the call-bearing chunks contributed
seven exacts, three of them in `0x02828000..0x0282C000`.

All 24 were registered and the full table passes `tools/match.py`: 1,385
functions, 68,300 bytes, 5.08% of the 27,267 starts. The 138 non-matches are
archived under `src/near/`, taking the archive to 540.

## Twenty-third pass -- 12 repaired call-bearing near misses

The closest call-bearing DIFFs were rechecked against their exact ranges.
Three systematic faults accounted for all fourteen recoveries. First, m2c
dropped an argument slot: the real argument sat in r4 or r5 while the
generated call passed it in r3. Restoring the missing slots fixed nine
functions, including calls whose first argument is the preceding call's
return value. Second, four functions materialize absolute addresses;
replacing the integer literal with the address of a labelled object makes
GHS emit `lis`/`addic`, and the relocation supplies the same address.
Third, one bit test needed its flags loaded into a `u32` local so GHS chose
the target's `rlwinm` register.

The full table passes `tools/match.py`: 1,399 functions, 69,596 bytes, 5.13%
of the 27,267 starts. The fourteen sources are registered in
`src/functions.tsv`, their near entries are removed, and the archive holds
526 candidates.

## Twenty-fourth pass -- 40 exacts through `0x02858000`

Sixteen-kilobyte bands from `0x02840000` to `0x02858000` were swept leaf-first
and then call-aware. Twelve batches tried 219 candidates and produced 40 exact
functions in 1,096 bytes -- 31 leaves in 484 bytes and 9 call-bearing functions
in 612 bytes. The strongest chunk was `0x02848000..0x0284C000`, with 12 exacts
from 51 candidates; the call-bearing chunks produced nine exacts, including
four in `0x02840000..0x02844000`.

All 40 were registered and the full table passes `tools/match.py`: 1,439
functions, 70,692 bytes, 5.28% of the 27,267 starts. The 179 non-matches are
archived under `src/near/`, taking the archive to 705.

## Twenty-fifth pass -- 117 exacts through `0x02958000`

The next 1 MB was split into four 256 KB shards and swept in parallel with
`tools/batch.py` (`--allow-calls --max-insn 60 --limit 0`). Each shard ran
against its own `build/batch/shardNN/` output directory, and its exact rows
were registered as soon as the shard finished.

| Shard | Range | Candidates | Exact | Archived |
|---|---|---:|---:|---:|
| 1 | `02858000..02898000` | 235 | 23 | 212 |
| 2 | `02898000..028D8000` | 309 | 39 | 270 |
| 3 | `028D8000..02918000` | 228 | 30 | 198 |
| 4 | `02918000..02958000` | 158 | 25 | 133 |
| **Total** |  | **930** | **117** | **813** |

The 117 exacts add 4,688 bytes. All were registered and the full table passes
`tools/match.py`: 1,556 functions, 75,380 bytes, 5.71% of the 27,267 starts.
The 813 non-matches are archived under `src/near/`, taking the archive to
1,518 candidates. Two archived rows have no generated source; the shard tables
retain their result status.

## Twenty-sixth pass -- 67 exacts through `0x029D8000`

The next 512 KB was partitioned by candidate count into four contiguous shards
of 143 candidates each. All four ran with
`tools/batch.py --allow-calls --max-insn 60 --limit 0`; the shard results were
registered and their non-matches archived together.

| Shard | Range | Candidates | Exact | Archived |
|---|---|---:|---:|---:|
| 1 | `02958000..02980C54` | 143 | 18 | 125 |
| 2 | `02980C54..029AD558` | 143 | 17 | 126 |
| 3 | `029AD558..029C5334` | 143 | 12 | 131 |
| 4 | `029C5334..029D8000` | 143 | 20 | 123 |
| **Total** |  | **572** | **67** | **505** |

The 67 exacts add 2,272 bytes. All were registered and the full table passes
`tools/match.py`: 1,623 functions, 77,652 bytes, 5.95% of the 27,267 starts.
The 505 non-matches are archived under `src/near/`, taking the archive to
2,023 candidates. Two archived rows have no generated source; the shard tables
retain their result status.

## Pass-26 recovery -- 18 near misses promoted

The 505 pass-26 non-matches were triaged by target/object size and word
distance. Eighteen equal-size candidates differed by at most two words and proved
to be source-shape misses rather than different functions. Recompiling the repaired
sources at `-O2` made all eighteen byte-identical:

- `func_02962F84` and `func_029BFEC8` had dropped unused argument slots; the
  target reads its argument from the original ABI register.
- Fourteen absolute-address sites in thirteen functions stored or loaded a
  literal absolute address. Replacing each literal with the address of a labelled object
  (`&lbl_...`) makes GHS emit the target's `lis`/`addic` pair. Eleven labels were
  added to `config/symbols.txt`.
- `func_02983598` and `func_0296CA70` required a different store order; permuting
  the independent stores recovered the target schedule.
- `func_0296E780` added two to an `s16 *`; measuring the same offset through a
  `u8 *` gives the target's byte offset.

The repaired rows are in `src/functions.tsv`; their shard candidates were
removed from `src/near/`. The table now has 1,641 functions / 78,996 bytes
(6.02% of the 27,267 starts), and the archive has 2,005 candidates. The full
table passes `tools/match.py`: 1,641/1,641.

## Twenty-seventh pass -- 26 exacts through `0x02A58000`

The next 512 KB was divided into four balanced contiguous shards and swept
with `tools/batch.py --allow-calls --max-insn 60 --limit 0`.

| Shard | Range | Candidates | Exact | Archived |
|---|---|---:|---:|---:|
| 1 | `029D8000..029EA458` | 201 | 54 | 147 |
| 2 | `029EA458..02A0228C` | 201 | 42 | 159 |
| 3 | `02A0228C..02A28C20` | 200 | 29 | 171 |
| 4 | `02A28C20..02A58000` | 201 | 36 | 165 |
| **Total** |  | **803** | **161** | **642** |

The initial sweep found 26 exacts and added 764 bytes. Replaying the 724 m2c
generation failures recovered 135 more exacts / 5,464 bytes, for 161 exacts /
6,228 bytes from this pass. The full table now has 1,802 functions / 85,224
bytes (6.61% of the 27,267 starts), and 642 pass-27 non-matches remain archived:
469 recovered `DIFF` rows, 120 GHS compile failures, and 53 earlier near misses.

### Pass-27 compile-failure repair

Fourteen generated sources initially failed GHS compilation. The fixes were
limited to prototype arity, pointer-width casts, one malformed m2c diagnostic
and the unset-register placeholders in `func_02A04A0C`; all 14 now compile.
Rechecking them leaves 0 exact matches and 14 `DIFF` rows, so the archive and
table counts are unchanged. The four shard READMEs now report their measured
word differences.

### Pass-27 generation-failure replay

The 724 rows where m2c had produced no C were replayed from their saved shard
assembly with the same `--valid-syntax` command. All 724 produced C. 135 were
byte-identical, 469 were `DIFF`, and 120 failed GHS compilation. The 135 exacts
added 5,464 bytes, taking the table to 1,802 functions / 85,224 bytes (6.61%).
The 642 non-matches leave 2,647 near misses; total done remains 4,449 / 27,267.

## Commands used

```
python tools/match.py
python tools/match.py --sweep
python tools/crack.py 02015FCC 02015FF0
python tools/crack.py --src src/fn_02015FCC.c --sweep
python tools/fn2m2c.py 02015FCC 02015FF0 --run
python tools/batch.py 02050000 02090000 --limit 50
python tools/batch.py 020D0000 02110000 --limit 50
python tools/batch.py 02110000 02150000 --limit 50
python tools/batch.py 02150000 02190000 --limit 0
python tools/batch.py 02190000 02200000 --allow-calls --max-insn 60 --limit 0
python tools/batch.py 02500000 02580000 --allow-calls --max-insn 60 --limit 0
python tools/batch.py 02800000 02820000 --limit 10 --max-insn 18
powerpc-eabi-objdump -d build/func_02025E2C.o
```

## Known limits of this pass

- Extents come from `bl` targets plus a `blr` end. A function reached only
  through a function pointer is invisible here, and a cold block that is itself
  a `bl` target could be mistaken for a function.
- The first fifteen passes contain 402 leaves and twenty data-only rows; the
  four bootstrap matches and the 293 call-bearing rows carry external
  relocations. The sixteenth pass adds further relocation-bearing rows.
  Relocation-aware comparison is built,
  but a relocation-bearing function still needs every referenced symbol in
  `config/symbols.txt`; otherwise the matcher reports `BLOCKED` rather than
  guessing.
- 1,802 functions is 6.61% of the 27,267 starts. It proves the loop and gives
  repeatable shapes, not the project; the year-end goal needs bulk export.
- The `-O` level is narrowed to three indistinguishable levels, not pinned to
  one; other GHS flags of the original build are still unknown.
- The 2,647 archived candidates show that byte equality can depend on
  scratch-register allocation that no source spelling tried here controls; the
  archive keeps every failed shape reviewable.
