# Project Yamamura -- Super Mario Maker decompilation research (Wii U)

A research decompilation of the 2015 Wii U title, reconstructing C from a
legally obtained copy for study of the engine's structure. The target is
`Block.elf`, the game's main executable (`00050000-1018DC00`, USA, v16).

Not affiliated with Nintendo. No game data, key, SDK, or compiler is included,
and nothing here can be assembled into a playable game. See
[`docs/PROVENANCE.md`](docs/PROVENANCE.md).

## PRIMARY STATUS

| | |
|:---|:---|
| **TARGET** | `Block.elf` (20,927,360 B, PowerPC big-endian) |
| **FUNCTIONS IDENTIFIED** | 27,267 |
| **FUNCTIONS MATCHED** | 1,641 |
| **FUNCTIONS NEAR** | 2,005 |
| **TOTAL DONE** | **3,646 / 27,267** (~13.37%) |

## SECONDARY STATUS

| | |
|:---|:---|
| **ENTRY POINT** | `0x02B8AECC` (`_start`), see [`docs/BOOTSTRAP.md`](docs/BOOTSTRAP.md) |
| **BOOTSTRAP SUBSYSTEM** | 5 runtime functions mapped; 4 byte-identical; `__init` is still a near miss |
| **IMPORT CALLS RESOLVED** | 8,704 call sites across 594 SDK entry points |
| **NAMED IMPORT EVIDENCE** | 7 call sites in 5 matched functions |
| **STRING EVIDENCE** | 1 code-related literal in 1 matched function |
| **NAMED SYMBOLS** | 64 in `config/symbols.txt` |
| **PROPOSED ROLE ALIASES** | 364 in `config/function_names.tsv` |
| **TOOLCHAIN** | GHS `ccppc` 5.3.27; per-row optimisation flags in `src/functions.tsv` |

## READABILITY ANALYSIS

The generated [function-name catalog](docs/FUNCTION_NAMES.md),
[source-grouping candidates](docs/FUNCTION_GROUPS.md), and
[human-readability guide](docs/HUMAN_READABLE.md) are proposals. They never
rename a verified symbol or move a matched row without a new byte check.

The optional `asm/import_calls.tsv` index adds named SDK evidence where a
call site falls inside a matched range. That overlap is currently small --
7 sites in 5 functions -- and is reported explicitly in
[`config/function_imports.tsv`](config/function_imports.tsv). The analyzer also
resolves exact-start code-related strings from `asm/rodata.txt`; only one
matched function qualifies, recorded in
[`config/function_strings.tsv`](config/function_strings.tsv). Raw `asm/` stays
gitignored: no disassembly dumps, rodata dumps, game assets or unrelated
game-facing text belongs in history.

## Progress

The twenty-sixth pass and its recovery audit have matched
**1,641 functions / 78,996 bytes** (6.02% of the 27,267 starts) and archived
**2,005 near misses**. The work began with early
leaf functions and the bootstrap chain, then added call-aware matching, the
selector-family repair, and leaf-first sweeps through `0x029D8000`. The first
subsystem -- entry point, chain, and constructor table -- is mapped, with both
bootstrap runtime functions reconstructed; `__init` is still a near miss.

See [`docs/DECOMPILATION.md`](docs/DECOMPILATION.md) for the pass-by-pass log
and [`docs/BOOTSTRAP.md`](docs/BOOTSTRAP.md) for the bootstrap map.

## What this repository contains

- `include/` -- reconstructed headers, currently `block.h` with the shared scalar types
- `src/` -- reconstructed C for matched functions, one function per file, plus [non-matching candidates](src/near/)
- `config/` -- `symbols.txt`, `splits.txt`, `target_layouts.tsv`, `gsys_methods.tsv`, and generated `function_names.tsv` / `function_imports.tsv` / `function_strings.tsv` / `function_groups.tsv` evidence inventories
- `docs/` -- the extraction pipeline, bootstrap map, decompilation notes, provenance, roadmap, source-shape plan, the naming/grouping/readability guides, the [external reference map](docs/REFERENCE_LIBRARIES.md), the [RTTI index](docs/RTTI_INDEX.md), the [middleware audit](docs/MIDDLEWARE_AUDIT.md), and the [target layout verification](docs/LAYOUT_VERIFICATION.md)
- `tools/` -- import indexing, a Ghidra labeler, an m2c slicer, a candidate loop, a batch driver, the byte matcher, the structure analyzer, and the RPX section extractor

## What it does NOT contain, and never will

- Any game asset, data file, disc image, or executable
- Any encryption key
- Any Nintendo SDK, Green Hills compiler, or licence file
- Any build that can be assembled into a playable game

## Tooling

| Tool | Purpose |
|---|---|
| `tools/import_index.py` | Build `imports_by_name.tsv` and `import_calls.tsv` from `.rela.text` |
| `tools/rtti_index.py` | Build `config/rtti_classes.tsv` from the local middleware string dump |
| `tools/rpx_extract.py` | Decompress a local Wii U RPX/RPL into an ignored ELF-like file for target-side layout and relocation analysis |
| `tools/LabelImports.java` | Ghidra script: create import stubs and name all 594 imports |
| `tools/fn2m2c.py` | Slice one function out of `main.s` into m2c-parsable assembly |
| `tools/match.py` | Compile a source file with GHS `ccppc`, apply its relocations and optional per-row flags, and diff it against the ELF word for word |
| `tools/crack.py` | Generate an m2c candidate, compile it, apply relocations, and show an instruction-aligned diff |
| `tools/batch.py` | Find eligible leaves or direct-call functions in a band, run the m2c/compile/compare loop, and log results to `build/batch/results.tsv` |
| `tools/analyze_structure.py` | Parse matched bodies plus optional named import calls and exact-start code strings, and emit role aliases, evidence tables, source-grouping candidates, and the docs |

`tools/ghidra_label_imports.py` is the Jython twin of the Java labeler, kept for
reference; the Java script is the one that runs.

## Verification

Byte matching needs the original compiler, so there is no CI and no
reproducible build in this repository:

```
python tools/match.py
python tools/match.py --sweep
```

The first compiles every row of `src/functions.tsv` with GHS MULTI 5.3.27,
applies the object's relocations from `config/symbols.txt`, and compares it
against the retail range, reporting `MATCH` only when bytes and size agree. It
exits non-zero if any row differs, fails to compile, or has an unresolved
relocation. The second repeats the comparison across optimisation levels.

Requirements are a licensed GHS `ccppc`, the extracted `Block.elf`, and the
listing/section artefacts described in [`docs/EXTRACTION.md`](docs/EXTRACTION.md).
None of those are redistributable.

## Layout

```
include/    reconstructed headers (block.h)
src/        matched C, one function per file; near misses in src/near/
config/     address map (symbols) and section boundaries (splits)
docs/       pipeline, entry point and bootstrap map, decompilation notes, provenance, roadmap
tools/      indexer, labeler, slicer, batch driver, matcher, RPX extractor
```

## Provenance

Every target byte derives from one copy of the game legally obtained by the
author and decrypted locally. No disc image, key, or extracted data is in this
repository. The chain and the measurements are recorded in
[`docs/PROVENANCE.md`](docs/PROVENANCE.md).

## Licence

`tools/` and `docs/` are MIT; see [`LICENSE`](LICENSE).

The reconstructed source in `src/` is a derivative work of the original program
and carries no licence to the underlying work; see
[`LICENSE-DECOMPILED`](LICENSE-DECOMPILED). Research and interoperability study
only.
