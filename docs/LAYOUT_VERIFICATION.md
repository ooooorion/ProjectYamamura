# Target layout verification

This is the target-backed follow-up to [`MIDDLEWARE_AUDIT.md`](MIDDLEWARE_AUDIT.md).
It records what the local executable shows about class sizes and constructor
offsets, and what it does **not** show. No game data, SDK file, compiler, or
external decompilation source is included in this repository.

## Evidence recovered

The local `Block.rpx` is an ELF32 big-endian container with zlib-compressed
sections. Decompressing it gives the same section layout as the disassembly:

| Section | VMA | Size |
|---|---|---:|
| `.text` | `0x02000020` | `0xC6E278` |
| `.rodata` | `0x10000000` | `0x181034` |
| `.data` | `0x10181040` | `0x2784C` |
| `.rela.data` | — | `0x88BC` |

[`tools/rpx_extract.py`](../tools/rpx_extract.py) performs this local conversion.
Its output is derived game data and is written under the gitignored `build/`
tree; it must never be committed.

A scan of every NUL-delimited `sead::`, `agl::`, and `gsys::` string in the
recovered `.rodata` found no absolute pointer to any of those strings in
`.rodata` or `.data`, and no `.rela.rodata`/`.rela.data` record whose computed
value points at one. This is evidence that these strings are **not** being used
as ordinary Itanium/GHS typeinfo name fields here. They may be debug, task, or
resource names. A class-name string therefore does not by itself establish a
class layout.

## SEAD

The constructor chain around `sead::ControllerMgr` is target-visible:

| Class | Target size | Target evidence | Reference assertion | Status |
|---|---:|---|---:|---|
| `sead::TaskBase` | `0x74` | `0x02783658` allocates 116 bytes when `this == null`; called by the next constructor | `0x74` | supported by constructor chain |
| `sead::CalculateTask` | `0xC8` | `0x02781D14` allocates 200 bytes and calls `0x02783658` | `0xC8` | supported by constructor chain |
| `sead::ControllerMgr` | `0xE8` | `0x02771C2C` allocates 232 bytes and calls `0x02781D14` with the string at `0x100EA354` (`sead::ControllerMgr`) | `0xE8` | verified |
| `sead::TaskMgr` | `0x1A4` | `0x0278423C` allocates 420 bytes; the final `MethodTreeNode` is at `+0x150` and ends at `0x1A4` | `0x1A8` | verified target layout; reference trailing fields absent |

The first three rows match their reference `static_assert` sizes exactly. The
`TaskBase` and `CalculateTask` names are inferred from the constructor nesting
and the matching sizes; only `ControllerMgr` has a direct class-name reference
at its allocation site.

The `TaskMgr` four-byte delta is resolved in the target. The constructor's
observed object layout is:

| Offset | Target content |
|---|---|
| `+0x00` | `hostio::Node` base storage |
| `+0x04..+0x3F` | `CriticalSection` (`0x3C`) |
| `+0x40` | parent framework, copied from `InitializeArg +0x14` |
| `+0x44` / `+0x48` | prepare thread / null fader task |
| `+0x4C..+0x93` | six list headers (12 bytes each) |
| `+0x94..+0xAB` | `HeapArray` (`0x18`) |
| `+0xB0` | maximum create queue size |
| `+0xB4` | root task |
| `+0xB8..+0x137` | `TaskBase::CreateArg` (`0x80`) |
| `+0x138..+0x14F` | `TaskMgr::InitializeArg` (`0x18`) |
| `+0x150..+0x1A3` | `mCalcDestructionTreeNode` (`0x54`) |
| `+0x1A4` | end of allocation |

The class-name string at `0x100EC45C` is used at `0x0278459C` as the root-task
name, not as a typeinfo pointer. The only direct call to `0x0278423C` is at
`0x02784678`, inside the following initialization helper. The target's final
field is the method-tree node, and its constructor writes continue through the
node's final words at `+0x1A0`; no object fields follow. The reference header's
final `_1a0`/`_1a4` fields do not fit this target's `+0x150` node placement;
the target has no post-node bytes. The allocation and node end are therefore
authoritative for `0x1A4`.

Observed `ControllerMgr` constructor writes include `+0x00` (base construction),
`+0x20`, `+0x70`, `+0xC8` (byte), `+0xCC` (multi-field initialisation), and `+0xD8`.
These offsets are evidence for future field naming, not a field map yet.

## AGL

A second target-side pass found no AGL constructor or vtable to promote. The
class-name strings are not typeinfo/vtable evidence:

- No `.rodata` or `.data` word points at an AGL class-name string, and no
  `.rela.rodata`/`.rela.data` record computes to one.
- `agl::lyr::Renderer` at `0x1012DC38` is used at `0x02944138` as a task-name
  argument, alongside `ParticleMgr` and `Debug`; it is not a constructor
  allocation site.
- `agl::utl::PrimitiveTexture` at `0x10172008` and
  `agl::utl::DynamicTextureAllocator` at `0x10172068` are used by the task and
  resource setup around `0x02BD75F4..0x02BD76E8`, not as typeinfo.
- None of the distinctive reference sizes `0xF78`, `0x247C`, or `0x11F4`
  occurs as an encoded `li` allocation immediate anywhere in `.text`. The
  common `0x80` size is not class-specific evidence. The nearby allocations at
  `0x02BD71A8` (`0x140`, `0x10C`) have no AGL class-name or vtable link.

No target AGL size or field offset is verified. The reference assertions remain
reference-only:

| Class | Reference size | Target status |
|---|---:|---|
| `agl::driver::GX2Resource` | `0x80` | unverified |
| `agl::lyr::Renderer` | `0xF78` | unverified |
| `agl::utl::DynamicTextureAllocator` | `0x247C` | unverified |
| `agl::utl::PrimitiveTexture` | `0x11F4` | unverified |

A future AGL pass must start from a target constructor, a recovered vtable, or
an allocation that is tied to an AGL class by more than a nearby string. The
Cafe reference remains useful for names and hypotheses only.

## GSys

`0x0294377C` is a strong constructor candidate for `gsys::SystemTask`:

- If `r3 == null`, it allocates `868` bytes (`0x364`) at `0x0294379C`.
- It calls `0x02783658` with the string at `0x1012DB38`
  (`gsys::SystemTask`); that base constructor allocates `0x74` bytes.
- It constructs six equally spaced method-tree entries starting at `+0x7C`,
  each `0x54` bytes apart. The name pointer in each entry is at `+0x14`:

| Entry base | Name field | Method entry | Method name |
|---|---:|---:|---|
| `+0x7C` | `+0x90` | `0x0294525C` | `gsys::SystemTask::PreCalc` |
| `+0xD0` | `+0xE4` | `0x029459C8` | `gsys::SystemTask::PostCalc` |
| `+0x124` | `+0x138` | `0x02946B14` | `gsys::SystemTask::DrawTV` |
| `+0x178` | `+0x18C` | `0x02946CCC` | `gsys::SystemTask::DrawDRC` |
| `+0x1CC` | `+0x1E0` | `0x02946D70` | `gsys::SystemTask::PostDrawTV` |
| `+0x220` | `+0x234` | `0x02946E0C` | `gsys::SystemTask::PostDrawDRC` |

The constructor stores each method entry in the node's delegate word at
`node +0x38` (object offsets `+0xB4`, `+0x108`, `+0x15C`, `+0x1B0`, `+0x204`,
and `+0x258`). Each target is a real `.text` function prologue; the mapping
follows the registration order and the six name strings above. The
machine-readable copy is [`config/gsys_methods.tsv`](../config/gsys_methods.tsv).
The object
continues through fields at `+0x284`, `+0x308` through `+0x35C`; the final
observed initialisation is at `+0x35C` and the allocation is `0x364`. This
establishes a concrete **layout skeleton** and six target entry points. It does
not establish the full field types or byte-identical C.

The next function at `0x02943EE4` references `ParticleMgr` and `Debug` and uses
fields including `+0x58`, `+0x44`, `+0x28C`, `+0x2B0`, and `+0x2B4`. Its exact
identity is not proven, so those offsets are not named in this pass. The
function at `0x0296A878` references `gsys::DrawObj` and stores into `+0xA4`; it
also remains a named candidate, not a matched function.

## What remains blocked

No `ccppc` is available in the worktree or on `PATH`. `tools/match.py` therefore
cannot compile or byte-verify a new GSys or SEAD/AGL function. The constructor
evidence above was obtained from the target disassembly and recovered sections;
no source was added to `src/` and no row was added to `src/functions.tsv`.

The next useful steps are:

1. Give the `ControllerMgr` constructor a named target row only after a matching
   source shape is found; its size is already verified.
2. Do not import the reference `TaskMgr` size `0x1A8`; the target layout is
   `0x1A4` and has no trailing post-node fields.
3. Use the six recorded GSys entry points with `tools/match.py` when a licensed
   GHS toolchain is available; no method body is byte-matched yet.
4. Locate an AGL constructor or vtable tied to a class before importing any AGL
   reference size; the current target pass found none.
