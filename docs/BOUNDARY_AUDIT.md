# Ghidra boundary audit

Generated 2026-11-20 from Ghidra 12.1.2 headless analysis.

## Clean run

- Clean boundary export: **40,782** functions
- Timed-out export: **40,782** functions
- Shared starts: **40,782**
- Clean-only starts: **0**
- Timed-out-only starts: **0**
- Changed end boundaries among shared starts: **0**
- Analysis timeout in clean log: **no**

## Cross-check against `bl` targets

- Direct `.text` `bl` targets: **27,267**
- Ghidra covered: **27,258**
- `bl` targets absent from Ghidra: **9**
- Ghidra-only starts (pointer-reached, thunks, cold blocks): **13,524**
- Exact starts present in Ghidra: **2,355 / 2,360**
- Exact starts absent from Ghidra: **5**

### Missing `bl` targets

These are real direct-call entries that Ghidra did not split into functions. Four are already verified exact rows; the other five are retained as untried `bl-target` rows.

| Start | First instruction | Containing Ghidra body | Inventory row |
|---|---|---|---|
| `020BCBB4` | `lis` | none | verified (exact) |
| `020BCBE0` | `lis` | none | verified (exact) |
| `020BCC0C` | `lis` | none | verified (exact) |
| `020BCC38` | `lis` | none | bl-target (untried) |
| `0259CE5C` | `lwz` | none | bl-target (untried) |
| `026AE8E8` | `mr` | none | bl-target (untried) |
| `02853F10` | `fmadds` | none | verified (exact) |
| `0286AA14` | `cmpwi` | none | bl-target (untried) |
| `02B3A68C` | `lwz` | none | bl-target (untried) |

## Tiny-function sample

There are **2,185** boundaries with `body_bytes <= 8`, including **1,010** four-byte boundaries. The sample below is stratified across the tiny set and includes exact matches.

| Start | Body bytes | Thunk | Status | First | Last | Insns | Verdict |
|---|---:|---:|---|---|---|---:|---|
| `02000E08` | 4 | 0 | untried | `blr` | `blr` | 1 | ends blr |
| `02054798` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `020547A0` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `020547A8` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `020547B0` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `0207C514` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `0207C54C` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `0207C9E0` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `021D0DD8` | 8 | 0 | exact | `li` | `blr` | 2 | ends blr |
| `026F0DE8` | 4 | 0 | untried | `blr` | `blr` | 1 | ends blr |
| `0273C9CC` | 8 | 0 | exact | `addi` | `blr` | 2 | ends blr |
| `02C6D410` | 8 | 0 | exact | `lwz` | `blr` | 2 | ends blr |

## Notes

- The clean run disables `Stack` before analysis; disassembly, function search, function creation, and the PowerPC constant-reference analyzer remain enabled.
- A boundary is not proof of semantic correctness. This audit checks coverage against the branch-target set and verifies that sampled tiny bodies contain plausible instructions and terminal flow.
- `ghidra_only` starts are expected because Ghidra also finds functions reached through pointers, thunks, and cold blocks that are not direct `bl` targets.
