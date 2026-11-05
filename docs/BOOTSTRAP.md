# Entry point and the bootstrap subsystem

Measured against `Block.elf` and `asm/main.s`. Every address here came from the
ELF header, a relocation, or the disassembly. The image has no game symbols, so
names are marked provisional where the evidence is a call site rather than a
match.

## Status

| | |
|---|---|
| Entry point | `0x02B8AECC` (`e_entry` in the ELF header) |
| Role | `_start`, the GHS runtime entry |
| Bootstrap functions mapped | 5 |
| Static constructors reachable | 1,021 |
| Byte-matched in this subsystem | 4 |
| First match target | `__init`, 132 bytes |

## The entry point

The ELF header points into `.text`, not at zero:

```
e_entry = 0x02B8AECC
.text   = 0x02000020 + 0x00C6E278
```

Three independent observations agree that this is the process entry and not an
ordinary function:

1. Nothing in the 98 MB disassembly branches to `0x02B8AECC`. Every earlier
   function in this project was found as a `bl` target; this one has no callers
   at all.
2. The instruction before it is `blr` (`0x02B8AEC8`), so it is a function
   boundary, not the middle of a function.
3. Its first calls resolve to `OSGetCurrentThread` and
   `OSIsDebuggerInitialized`, and its remaining calls are the GHS runtime
   (`__init`, `__cpp_exception_*`, `__ghs_mtx_*`, `exit`). That is startup code.

```
02b8aecc  mflr    r0
02b8aed0  stwu    r1,-24(r1)
02b8aed4  stw     r30,16(r1)
02b8aed8  stw     r31,20(r1)
02b8aedc  mr      r31,r4
02b8aee0  mr      r30,r3
02b8aee4  stw     r29,12(r1)
02b8aee8  stw     r0,28(r1)
02b8aeec  bl      OSGetCurrentThread
02b8aef0  mr      r29,r3
02b8aef4  bl      OSIsDebuggerInitialized
02b8aef8  cmpwi   r3,0
02b8aefc  beq     02b8af18
02b8af00  lis     r4,625          ; 0x02710000
02b8af04  lis     r5,697          ; 0x02B90000
02b8af08  addi    r4,r4,5376      ; 0x02711500
02b8af0c  li      r3,2
02b8af10  addi    r5,r5,-20920    ; 0x02B8AE48
02b8af14  twu     r30,r0          ; trap when a debugger is attached
```

## The chain

| Address | Name | Bytes | Evidence |
|---|---|---|---|
| `0x02B8AECC` | `_start` | 404 | `e_entry`; zero callers |
| `0x02B8AE48` | `__init` | 132 | walks the constructor table; called by `_start` and again by `0x02711500` |
| `0x02BCF5D0` | `startup_register` | 104 | **matched**; called by `_start` with `0x02BCF67C`; takes a lock and stores that pointer in a 36-slot table |
| `0x02711500` | `runtime_init` | 80 | stores its two arguments at `0x10189810`/`0x10189814`, calls `__init` then `0x02713190` |
| `0x02713190` | `main` (provisional) | 1,044 | one caller; writes "Application Start"/"Application Start Time" markers and installs exception callbacks |

Extents were read from the terminating `blr`, not from the `bl`-target
heuristic. The heuristic overruns here: `_start` has no callers, so the next
`bl` target after `__init` is `_start`'s own callee, not `__init`'s end.

### `_start`, 0x02B8AECC..0x02B8B060

In order:

1. `OSGetCurrentThread`, then `OSIsDebuggerInitialized`; when a debugger is
   present the registers are primed (`2`, `0x02711500`, `0x02B8AE48`) and the
   function executes an unconditional trap.
2. Two weak-symbol blocks are skipped in this build. Their guard symbols are
   undefined (`$UNDEF`, value 0), so the code that would clear the
   `__cpp_exception_init_ptr`/`__cpp_exception_cleanup_ptr` cells and call the
   weak exception hooks (`0x04000000` placeholders) is not executed.
3. `__init()`.
4. `startup_register(0x02BCF67C)`.
5. `runtime_init(r3, r4)`, forwarding the registers the loader supplied.
6. `cmplw r30, 0xDEADEFED` (`lis r0,-8531; ori r0,r0,61453`). On equality it
   runs the cleanup block (`memcpy`, `__ghs_mtx_init`, `__ghs_mtx_lock`,
   `__ghs_mtx_unlock`) and calls `exit(0)`; otherwise it returns normally.

### `__init` and the constructor table

`__init` is 132 bytes at `0x02B8AE48..0x02B8AECC`. It is guarded by a word at
`0x101A4FC0`:

- if the word is non-zero, it returns immediately;
- otherwise it sets the word to 1, then walks the table at `0x1018003C`.

That table holds **1,021 function pointers** followed by a null terminator. All
1,021 point into `.text`:

```
0x1018003C -> 0x02003930, 0x02004960, 0x020064E0, 0x020083CC, ...
last       -> 0x02C6DB58
```

This is the static-initialisation surface of the game. It spans almost the
whole text section, from `0x02003930` to `0x02C6DB58`, so constructors are not a
contiguous region; they are scattered through the image and reached only
through this table.

`runtime_init` calls `__init` a second time. The guard makes that call a no-op
when `_start` already ran, so the table is executed exactly once either way.

### `runtime_init`, 0x02711500..0x02711550

```
mr      r31,r3
mr      r30,r4
bl      __init
stw     r31,0x10189810
stw     r30,0x10189814
bl      0x02713190
li      r3,0
blr
```

The two globals are where the loader's arguments are recorded. The return value
is always zero, so the process result does not come from `main`'s return value.
This function is byte-matched at 80 bytes; the source is
`src/fn_runtime_init.c`.

### `startup_register`, 0x02BCF5D0..0x02BCF634

The 104-byte reconstruction takes the startup lock, stores
`func_02BCF5CC` in the callback cell at `0x02C745E0`, and scans 36 entries of
12 bytes at `0x1034C000`. The first slot with a null `+0x08` pointer receives
the argument and is linked with `func_02BCF688`; success unlocks and returns
zero. A full table unlocks and returns `-1`. `-Ospace` emits the
`_savesmall_16`/`_restsmall_16` helpers, both named in `config/symbols.txt`.
Source: `src/fn_startup_register.c`.
Its two adjacent helpers are also matched: the four-byte tail thunk
`func_02BCF5CC` and the 40-byte link insertion `func_02BCF688`.

### `main`, 0x02713190..0x027135A4

1,044 bytes, 261 instructions, 27 unique `bl` targets: 21 internal functions
and 6 imports. The opening sequence:

```
0x027131AC  call 0x02769508 with 0x100DF7A8 ("Application Start Time"), 1
0x027131BC  call 0x027695B4 with 0x100DF788 ("Application Start"), 1
0x027131C0  OSGetSystemTime
0x027131F8  OSBlockThreadsOnExit
0x02713200  MEMGetBaseHeapHandle(1)
0x02713208  MEMGetAllocatableSizeForExpHeapEx(heap, 4)
0x02713220  OSReport with 0x100DF7C0 ("allocatable size %8d(KB),%5d(MB)")
0x02713234  OSSetExceptionCallbackEx(4, 2, 0x02711620)
0x02713248  OSSetExceptionCallbackEx(4, 3, 0x02711620)
0x0271325C  OSSetExceptionCallbackEx(4, 6, 0x02711620)
```

The 21 internal callees, in address order, are:

```
0x027119E4  0x027119F0  0x02712374  0x02712414  0x02712424  0x02712DFC
0x02713140  0x02730CB0  0x027435EC  0x02769508  0x027695B4  0x0276FBA4
0x02773DCC  0x027824DC  0x02782520  0x02783918  0x027862AC  0x027864F4
0x02790060  0x02794110  0x0294362C
```

`0x0276FBA4` is called as `(1216, object, 4)` and looks like the allocator;
naming it is part of the next layer, not this map.

## Import surface

| Module | Imports reached by the bootstrap chain |
|---|---|
| coreinit | `OSGetCurrentThread`, `OSIsDebuggerInitialized`, `OSGetSystemTime`, `OSBlockThreadsOnExit`, `MEMGetBaseHeapHandle`, `MEMGetAllocatableSizeForExpHeapEx`, `OSSetExceptionCallbackEx`, `OSReport`, `memcpy`, `__ghs_mtx_init`, `__ghs_mtx_dst`, `__ghs_mtx_lock`, `__ghs_mtx_unlock`, `__ghsLock`, `__ghsUnlock`, `exit` |
| coreinit (data) | `__cpp_exception_init_ptr`, `__cpp_exception_cleanup_ptr`, `__ghs_mtx_dst` |
| sysapp | none; `SYSRelaunchTitle` at `0x02713674` belongs to the function after `main` |

Every name above came from `asm/import_targets_expected.tsv`, not from a guess
at the disassembly text.

## What is not settled

- `main` is still a provisional name, identified by its call site and
  behaviour; `startup_register` is now proven by a byte match.
- The `0xDEADEFED` comparison is measured, not explained. It selects a cleanup
  path that ends in `exit(0)`; the ordinary loader path does not take it.
- The weak `__cpp_exception_init`/`__cpp_exception_cleanup` calls are unresolved
  in this image; their guard symbols are `$UNDEF` (zero), so both blocks are
  skipped before the cells are touched.
- `startup_register` writes into a 36-slot table at `0x1034C000` (in `.bss`);
  the table's purpose is not established.
- The 21 internal callees of `main` are mapped by address only.

## First match targets

| Function | Bytes | Why |
|---|---|---|
| `__init` | 132 | small; two globals, one table walk; the first target that needs `ADDR16` relocation handling |
| `runtime_init` | 80 | **matched**; four instructions of setup, two calls, two globals |
| `startup_register` | 104 | **matched**; lock/unlock pairs and a 36-iteration loop |
| `main` | 1,044 | too large for a first match, but its prefix is a useful C reconstruction after the helpers |

`tools/match.py` now applies object relocations resolved through
`config/symbols.txt`, so the table and guard references are comparable. A
`__init` candidate exists but is not byte-identical: the target is 132 bytes,
while the tested source shapes produce 100 bytes at `-O2`, 120 bytes at `-O1`
and 124 bytes at `-O1 -Onocse`. The remaining difference is loop/register
allocation, not relocation resolution; the candidate is kept out of `src/`.
