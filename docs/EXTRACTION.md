# Extraction notes — RPX to readable executable

This document starts from a `Block.rpx` extracted from a copy of the game the
reader legally owns. It deliberately does **not** cover obtaining, dumping, or
decrypting the disc, and it records no keys or key-derivation steps. Those
stages are out of scope for a public repository. The stage numbers are kept
from the original pipeline; stages 0-2 were local acquisition steps.

The goal is one artifact: **the game's main `.rpx`, converted to an `ELF32`
big-endian PowerPC file with a disassembly you can grep.** Ghidra, m2c and
matching sit downstream of that.

## Inputs

- `Block.rpx`, extracted from a legally obtained copy.
- `wiiurpxtool` to convert RPX to ELF.
- A PowerPC binutils toolchain (`objdump`, `strings`, `nm`).
- Optional: Ghidra with the Wii U loader, and `m2c`.

The retail executable is title version v16 and reports Café SDK 2.12.13.
Matching against a different build can diverge on inlining and library codegen.
The repository contains no executable, disc image, key, SDK, or compiler.

## Stage 3 — .rpx to ELF

**Result: `Block.elf`, 20,927,360 bytes, `elf32-powerpc`, disassembling from `02000020`.**

```bash
wiiurpxtool -d Block.rpx Block.elf      # positional output, no -o flag
```

As shipped by `wiiurpxtool`: `ELF32`, big-endian, 40 section headers, **no program headers**,
`e_entry 0x02b8aecc`, `e_ident` `7f 45 4c 46 01 02 01 ca fe` (the `CA`/`FE` are Nintendo's
OSABI/ABIVERSION bytes — harmless, leave them).

### Mandatory repair: `.symtab` `sh_info`

`objdump` rejects the raw output with `file format not recognized`, while `readelf` reports a
perfectly clean header — it never validates this field.

Cause: `shdr[35]` (`.symtab`) carries `sh_info = 405902` while the table holds 641 symbols
(`sh_size 0x2810` / 16). BFD requires `sh_info <= sh_size / sh_entsize` and abandons the whole
file on that one field. Offset `0x5D4 = e_shoff (64) + 35*40 + 28`, value `1`:

```powershell
$p = '.\Block.elf'
$b = [IO.File]::ReadAllBytes($p)
$b[0x5D4]=0; $b[0x5D5]=0; $b[0x5D6]=0; $b[0x5D7]=1
[IO.File]::WriteAllBytes($p, $b)
```

Also normalize `e_type` `0xFE01 → 2` at `0x10` and `e_machine` `0x0D0A → 20` at `0x12`, so BFD
selects `elf32-powerpc` instead of the generic `elf32-big` fallback. Those two fields are *not*
what breaks `objdump`: `0xFE01`, `0x0D0A` and zero program headers are each accepted (tested
individually). **Check `sh_info` first on every fresh conversion from this SDK.**

### Section layout

| Section | VMA | Size | Note |
|---|---|---|---|
| `.syscall` | `0x02000000` | `0x8` | `nop; blr` trampoline |
| `.text` | `0x02000020` | `0xC6E278` | 12.43 MiB of game code — the decomp surface |
| `.rodata` | `0x10000000` | `0x181034` | strings, RTTI, assert text — highest early value |
| `.data` | `0x10181040` | `0x2784C` | |
| `.module_id` | `0x101a88a0` | `0x160` | |
| `.bss` | `0x101a9000` | `0x1A3978` | |
| `.rela.text` | — | `0x4D1BC4` | 421,243 relocations |
| `.rela.rodata` | — | `0xFBEF8` | |
| `.rela.data` | — | `0x88BC` | |

`shdr[38]`/`shdr[39]` use Nintendo's `0x80000003`/`0x80000004` (RPL exports/imports). Imports
resolve to 25 `.fimport_*` sections — `nlibcurl nsysnet gx2 snd_core snd_user nn_save vpad
vpadbase proc_ui nn_ac padscore coreinit sysapp zlib125 mic nn_act nn_olv2 nn_boss nn_fp nn_ndm
nn_nfp nn_acp` — plus `.dimport_coreinit`, `.dimport_nn_act`, `.dimport_nn_boss`.

### Symbols: no game names, all import names

`.symtab` survives but holds **no game functions**: 40 section symbols, `$TEXT`/`$DATA`/`$UNDEF`,
and 595 `FUNC` entries that are every one an import stub in `.fimport_*` — zero in `.text`. So
game code is wholly `FUN_xxxxxxxx`, while every SDK entry point has a real name:

```bash
objdump -t Block.elf | grep '\.fimport_' | head
# curl_easy_cleanup, NSSLAddServerPKIGroups, GX2BeginDisplayListEx, AXAcquireVoiceEx,
# SAVEFlushQuota, VPADControlMotor, COSWarn, inflate, ACPMiiUnwrap, …
```

That is why the import names, not the entry point, are the first anchors into this binary.

---

## Stage 4 — Produce greppable text artifacts

**Result: passed, 2026-11-02.** Four artifacts in `asm/` (throwaway, gitignored,
regenerated at will):

| File | Bytes | Lines | Produced by |
|---|---|---|---|
| `main.s` | 98,713,138 | 3,258,470 | `objdump -d --no-show-raw-insn -j .text` |
| `rodata.txt` | 6,406,736 | 98,568 | `objdump -s -j .rodata` (hex + ASCII) |
| `sections.txt` | 4,103 | 71 | `objdump -h` |
| `strings.txt` | 352,767 | 22,738 | `powerpc-eabi-strings -n 6` |

All four are plain ASCII — no BOM, no NUL, no byte above `0x7F`, CRLF endings — so they are safe
for `grep`, `diff` and `objdiff`. Regeneration takes about 11 seconds.

```powershell
$obj = "$env:DEVKITPPC\bin\powerpc-eabi-objdump.exe"
New-Item -ItemType Directory -Force -Path .\asm | Out-Null

& $obj -d --no-show-raw-insn -j .text Block.elf | Out-File -Encoding ascii .\asm\main.s
& $obj -h Block.elf            | Out-File -Encoding ascii .\asm\sections.txt
& $obj -s -j .rodata Block.elf | Out-File -Encoding ascii .\asm\rodata.txt
& "$env:DEVKITPPC\bin\powerpc-eabi-strings.exe" -n 6 Block.elf |
    Out-File -Encoding ascii .\asm\strings.txt
```

Two PowerShell traps, both of which fail in ways that look like tool bugs:

1. **`>` is relative to the current directory.** From a toolchain `bin`
   directory, `> asm/main.s` fails with `Could not find a part of the path`.
   Run from the project root, or use absolute paths.

2. **Windows PowerShell 5.1 `>` writes UTF-16LE with a BOM**, doubling the file and breaking
   `grep`/`diff`/`objdiff`. Always pipe through `Out-File -Encoding ascii`.

`-j .text` matters: without it, `-d` also emits `.syscall` and the 25 `.fimport_*` sections,
which are import thunks rather than game code.

`strings` ships as `powerpc-eabi-strings.exe` in the same binutils `bin`
directory (not necessarily on `PATH`).
`-e b` means *16-bit* big-endian, not "big-endian machine" — plain ASCII needs no flag; `-e B`
and `-e L` are for UTF-16/32 text.

Gate 4: `main.s` opens with `02000020 <.text>:` then `mflr r0` / `stwu r1,-24(r1)`, and
`sections.txt` reports `.text` as `00c6e278`. **The toolchain is proven** — everything upstream
of this point was plumbing.

### Import index

Two derived tables, regenerated by `tools/import_index.py`:

| File | Columns | Rows |
|---|---|---|
| `asm/imports_by_name.tsv` | `calls`, `module`, `name`, `stub` | 594 |
| `asm/import_calls.tsv` | `caller`, `kind`, `module`, `name`, `stub` | 8704 |

Build this from `.rela.text`, **not** by scanning `main.s` for branch targets.

The branch target at a call site is real, but it is not the runtime stub. The 594 distinct
targets occupy `0x02C6E2A8`..`0x02C77078`, a 36 KB window that starts 16 bytes past the end of
`.text` and belongs to no section. There is exactly one per import and their order matches
`.fimport_*` order, so they are the link-time addresses of that stub table. The `.fimport_*`
sections themselves hold eight zero bytes per import behind an 8-byte `{count, crc}` header and
are filled in by the loader at run time. `objdump` has no symbol for the window, so it prints
the nearest one: `bl 2c74520 <curl_easy_cleanup-0xbd391e28>`.

The `R_PPC_REL24` relocation whose symbol *is* the import names the callee directly, so the
relocation offset is the caller. Applying those relocations is worse than ignoring them: the
displacement is recomputed as `S + A - P` with `S = 0xC0007008`, and since `0xC0000000` is an
exact multiple of the 26-bit branch modulus, the wrap collapses every call to
`stub - 0xC0000000` -- the site at `0x02001584` becomes `bl 0x7008` instead of `bl 0x2C73398`.
Ghidra's ELF loader does this under "Perform Symbol Relocations". That tick tends to come
back by itself in the import dialog whenever the format, the language or "Refresh" is
touched, so set it last -- or leave it on: it repairs the `lis`/`addi` data pointers, and
`tools/LabelImports.java` names the collapsed targets (`stub - 0xC0000000`, `0x006348`..`0x0079D0`) just
as well as the raw ones.

`kind` is `bl` for a call and `b` for a tail call (240 of those). `grep '^020b1e34'` on
`import_calls.tsv` answers "what does this instruction call"; `grep -i inflate` on
`imports_by_name.tsv` answers "how hot is this API".

594 of the 595 imports are called directly. The exception,
`nn_olv2.rpl/__ct__…DownloadedCommentData`, is reached through a computed address instead
(`lis`/`addi` pair at `0x020873ce`), which is also why its stub shows a type-4/type-6 reloc pair
rather than a `REL24`.

---

## Stage 5 — Load into Ghidra

Import the **`.elf`**, not the `.rpx` — you already decompressed it, and the ELF carries the
section boundaries cleanly.

- Language/compiler spec: pick from the Wii U processor definitions that `GhidraRPXLoader`
  bundles (Gekko/Broadway/Espresso). **Do not use stock `PowerPC:BE:32:default`** — it has
  no paired-singles, and this code uses `psq_l`/`ps_add` constantly.
- If you do import the `.rpx` directly through the loader, run its bundled
  `fix_primary_imports.java` afterwards so import stubs get named instead of landing in
  `.data` as garbage.
- Let full auto-analysis finish. On a title this size, expect a long coffee break.
- Then run `tools/LabelImports.java` (Script Manager -> Run Script; it is Java because
  12.x ships Jython only as an optional extension). It names the 594 import targets, so
  every SDK call decompiles as `OSBlockMove(...)` instead of a bare address. Expect
  `functions created: 594 | label only: 0`.

Afterwards, the anchor points are the **imports** — `coreinit`, `gx2`, `nn_*`,
`nn::act`, `nn::fnd` — because those are the only functions with real names. Start
your understanding of the code by looking at what SDK services it calls, not at the
entry point.

---

## Stage 6 — Dynamic confirmation (optional, later)

Cemu exposes a GDB stub on **port 1337**:

```bash
powerpc-eabi-gdb Block.elf
(gdb) target remote localhost:1337
```

Practical caveats: this requires an extracted, decrypted layout, and the ELF's section
addresses won't necessarily match the loaded image without offsetting. Treat it as a tool
for answering *specific* questions ("what is this struct actually shaped like at runtime"),
not as a general debugging environment.

---

## Stage 7 — The actual first deliverable

Do not begin by decompiling `main`. Pick one small, verifiable target and finish it end to end;
that is how the toolchain gets proven before weeks are bet on it.

The loop is **string -> address -> code -> function -> m2c -> read**, and every step needs a
different artifact, because `main.s` can only cover part of the third one:

| Step | Source | Why not `main.s` |
|---|---|---|
| find a string | `asm/strings.txt`, `asm/rodata.txt` | it holds `.text` only (`-j .text`) |
| get its address | `objdump -s` row label (already a VMA), or `strings -t x` offset + the section's `sh_addr - sh_offset` | `strings.txt` carries no addresses |
| find the code | `main.s` immediates, or a Ghidra xref | no symbol names, no function boundaries |
| function extents | Ghidra (function start/end) | one `.text` label for all 12.4 MiB |
| decompile | `tools/fn2m2c.py` -> `m2c -t ppc` | objdump syntax is not m2c input |

### From string to address

`asm/strings.txt` is `strings` output: the text, never an address. Both routes need the section
table (`asm/sections.txt`, or `objdump -h`), because an address and a file offset are different
numbers.

**`objdump -s` row labels are addresses.** `objdump -s -j .rodata Block.elf` prints 16 bytes per
row, and the leading hex is the **VMA** of that row's first byte -- not an offset into the file
and not an offset into the section. Take the row label and add the byte position of the
character inside the row:

```
 1000b450 02 06 09 a4 69 6e 76 61 6c 69 64 20 76 65 63 74  ....invalid vect
 1000b460 6f 72 3c 54 3e 20 73 75 62 73 63 72 69 70 74 00  or<T> subscript.
```

"invalid vector<T> subscript" starts four bytes into row `0x1000B450`, so it is at `0x1000B454`.
It also straddles the row boundary, which is the trap: `grep 'invalid vector' rodata.txt` misses
this copy entirely, because the ASCII column holds only `invalid vect` and then `or<T> subscript`.

**`strings -t x` prints file offsets, not addresses.** Convert through the section header. For
`.rodata` (`sh_addr 0x10000000`, `sh_offset 0x840`):

```
VMA = 0x10000000 + (file_offset - 0x840)
```

There is no global base: every section needs its own `sh_addr`/`sh_offset` pair, and `.data`,
`.bss` and the import stubs do not share `.rodata`'s.

A message is not unique, so do not treat the first hit as *the* address. "invalid vector<T>
subscript" exists four times -- `0x1000B454`, `0x1013E990`, `0x1013EA00`, `0x10151DA4` -- because
separate runtime libraries each ship a copy. Which one matters is decided by the code that loads
it, and that is the next step.

### Grep the address, and expect it in decimal

`objdump` prints immediates in **decimal**, so `0x1000B454` never appears as text. A rodata
pointer is a `lis`/`addi` pair; split the address first:

```
hi = (addr + 0x8000) >> 16     # 0x1001
lo = addr - (hi << 16)         # 0xFFFFB454 -> -19372
```

then look for `lis rX,4097` with `addi rX,rX,-19372` a few instructions later. The `0x8000` is
not decoration: it keeps the low half inside 16 signed bits, so `0x1000B454` rounds the high half
*up* to `0x1001`. Pairing `lis rX,4096` with the same `addi` reconstructs `0x0FFFB454` instead --
wrong by 64 KiB and plausible enough to waste an afternoon. Matching the `addi` alone helps
nobody either: `-19372` occurs five times in the whole 3.26M-line listing.

Read the `lis` out of the listing rather than assuming it, and let the relocations confirm the
pair: `R_PPC_ADDR16_HA` at `0x02061C1E` and `R_PPC_ADDR16_LO` at `0x02061C22` both carry addend
`0xB454`.

### Worked example (verified on this binary)

```
string    "invalid vector<T> subscript"      0x1000B454
code      lis r4,4097 / addi r4,r4,-19372   0x02061C20
function  0x02061BBC .. 0x02061CEC          77 instructions
```

```bash
python tools/fn2m2c.py 02061BBC 02061CEC --run
```

First-pass output, unedited:

```c
s32 func_02061BBC(void *arg0, u32 arg1) {
    ...
    if ((temp_r5 == 0) || ((u32) ((arg0->unk8 - temp_r5) / 88) <= arg1)) {
        func_02060A44(&sp30, 0, 0);
        var_r12 = (void *) 0x1000B453;
        do { temp_r0 = var_r12->unk1; var_r12 += 1; } while ((s32) temp_r0 != 0);
        func_02060F8C(&sp30, var_r12 - 0x1000B454);
```

A string-length scan feeding a throw helper: that is a `std::vector` subscript check, and it
names three callees by address. Gate 7 is passed when a function like this reads as code you
can describe, not as noise.

### Why the slice tool exists

m2c parses GNU-as style assembly, not objdump output. Three things must be repaired first, and
`tools/fn2m2c.py` does all three:

- **Branch targets must be labels.** `beq 2061c0c` and `beq 0x2061c0c` both die with
  `Failed to parse instruction`; `.L002061C0C` parses.
- **The `<...>` annotations must be dropped.** All 8,708 import call sites carry
  `curl_easy_cleanup-0x...`, which is wrong for 8,707 of them (Stage 4 explains why).
- **One labelled function per file**, because `-f` keys off that label.

```bash
python tools/fn2m2c.py START END [--asm main.s] [--out func.s]
                      [--m2c path/to/m2c.py] [-t ppc] [--run]
```

`-t ppc` is enough. `-t ppc-mwcc-c` gives identical output on this function -- the build is GHS
MULTI 5.3.27, not CodeWarrior -- so do not chase MWCC-specific idioms.

`tools/crack.py START END` wraps that slice, m2c, GHS compile, relocation
application and objdump diff in one command; `docs/DECOMPILATION.md` records
the candidate workflow.

After the gate, scale up: pick the next function by the SDK call it makes, not by address order.

Stage 7 has been executed on the 1,667 functions in `src/`; all 1,667 compile
byte-identical to `Block.elf` with `python tools/match.py`.
`docs/DECOMPILATION.md` records the loop, the toolchain setup, and the three
codegen traps (return type, CR mask, source shape).

## Failure modes, collected

| Symptom | Cause |
|---|---|
| ELF is little-endian | Input wasn't an RPX/RPL |
| Ghidra shows garbage during paired-single ops | Stock PowerPC processor spec in use |
| `strings` finds nothing useful | Look in `.rodata` via `objdump -s`, not just `strings` |
| `ccppc` licence error | A valid local GHS installation is required; no licence material is included |
| `Failed to parse instruction ...: beq 2061c0c` | m2c wants labels, not numbers -- route functions through `tools/fn2m2c.py` |
| m2c output is a wall of `?` / `unk` | First pass over untyped code; add prototypes and stack structs with `--context` |
