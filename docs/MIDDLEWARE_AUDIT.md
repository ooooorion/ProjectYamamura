# Middleware reference audit

This audit compares the middleware names visible in `Block.elf` with the
available Wii U references. It is a name-level review, not a binary diff. No
external source was copied into this repository. This pass does not by itself
claim target class sizes; the target-backed exceptions are kept in
[`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md).

The target-side source of names is the local, gitignored string dump. The
generated index and counts are in [`RTTI_INDEX.md`](RTTI_INDEX.md) and
[`config/rtti_classes.tsv`](../config/rtti_classes.tsv).

## Method

1. Extract namespace-qualified strings for `nn::nex`, `sead`, `agl`, `gsys`, and
   `nw::snd` with [`tools/rtti_index.py`](../tools/rtti_index.py).
2. Extract FFL identifiers from the same dump separately, because the FFL
   evidence is mostly resource names rather than `ffl::` RTTI.
3. Search the local reference checkouts for exact `class`/`struct`
   declarations, then for leaf-name and member-name occurrences.
4. Classify each target string as exact, leaf-only, member/marker, related, or
   absent. Only names are recorded here; target-backed layout evidence is kept
   in [`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md).

Reference snapshots used here:

| Reference | Snapshot | Scope |
|---|---|---|
| [SEAD](https://github.com/aboood40091/sead) | `4b48682` | Cafe-era SEAD and its `packages/agl` Wii U AGL implementation. |
| [FFL](https://github.com/aboood40091/ffl) | `73fe9fc` | FFL `1.3.10`, older than the target's `1.5.6`. |
| NintendoWare for Cafe | `1.14.8` package | Newer than the target's `1.14.5`; headers only. |
| [Pretendo NEX](https://github.com/PretendoNetwork/nex) and related repositories | Protocol references | Current protocol implementations, not the target's NEX `3.8.3` C++ client. |

## Result summary

| Component | Target strings | Exact declarations | Result |
|---|---:|---:|---|
| NEX | 559 unique / 883 occurrences | 0 | Names only; no public 3.8.3 C++ layout. |
| NW4F | 1 unique / 1 occurrence | 0 | One leaf match to `nw::snd::internal::TaskThread`; target omits `internal`. |
| SEAD | 25 unique / 25 occurrences | 6 | Six exact classes; two member strings; seventeen related or absent names. |
| AGL | 12 unique / 13 occurrences | 6 | Six exact classes, two namespace-shifted leaves, one marker, three absent. |
| FFL | 26 identifiers | 4 | Four low-level allocator/zlib classes; no public 1.5.6 rendering API. |
| GSys | 18 unique / 23 occurrences | 0 | Target-only; no public decompilation. |

“Exact” means the target and reference use the same namespace and class name.
It still does not prove a matching layout. The constructor-chain evidence in
[`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md) is a separate target-side
check.

## NintendoWare for Cafe

The only target-side NW4F class string is `nw::snd::TaskThread`. The 1.14.8
package declares the class as `nw::snd::internal::TaskThread` in
`NW_Cafe/Library/Snd/include/nw/snd/snd_TaskThread.h`.

This is a leaf-level match, not an exact one. The target may have a different
namespace or a demangled string that omits `internal`; do not use the 1.14.8
class body as a target layout. The header is useful for API naming only. The
target's NW4F version is `1.14.5`, and the package release notes warn that
G3d/Lyt binary formats changed between 1.14.5 and 1.14.8.

No other NW4F class names appear in the target string index. NW4F is statically
linked, so its functions are reached through the static code and headers, not
through an `.fimport` module.

## SEAD

The target has 25 `sead::` strings. Six have exact class declarations in the
SEAD reference:

| Target | Reference | Notes |
|---|---|---|
| `sead::ControllerMgr` | `engine/library/include/controller/seadControllerMgr.h` | Exact class. |
| `sead::FileDeviceMgr` | `engine/library/include/filedevice/seadFileDeviceMgr.h` | Exact class. |
| `sead::MethodTreeMgr` | `engine/library/include/framework/seadMethodTreeMgr.h` | Exact class. |
| `sead::ResourceMgr` | `engine/library/include/resource/seadResourceMgr.h` | Exact class. |
| `sead::TaskMgr` | `engine/library/include/framework/seadTaskMgr.h` | Exact class. |
| `sead::ThreadMgr` | `engine/library/include/thread/seadThread.h` | Exact class. |

The target-side constructor chain gives a second check, independent of the
name table:

- `0x02783658` allocates `0x74` bytes and is the `sead::TaskBase` base
  constructor candidate.
- `0x02781D14` allocates `0xC8` bytes and calls it; this is the
  `sead::CalculateTask` candidate.
- `0x02771C2C` allocates `0xE8` bytes, calls `0x02781D14`, and references
  `sead::ControllerMgr`, matching the reference assertion exactly.
- `0x0278423C` allocates `0x1A4` bytes and places the final
  `MethodTreeNode` at `+0x150..+0x1A3`; the target object ends at `0x1A4`. The
  reference's trailing `0x1A8` layout is not present in this build.

Only the `ControllerMgr` row has a direct class-name reference at its
allocation site; the `TaskBase`/`CalculateTask` names come from the nesting and
the matching sizes. `TaskMgr` uses its class-name string at `0x0278459C` as the
root-task name, not as typeinfo. Its target field layout and `0x1A4` size are
verified in [`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md).

The remaining strings are not exact class matches:

| Target | Classification | Reference finding |
|---|---|---|
| `sead::AppCalc` | absent | No declaration; likely a target-side task class. |
| `sead::AudioTaskThread` | absent | No declaration; likely target-side audio integration. |
| `sead::BtmAppDraw` | absent | No declaration. |
| `sead::BtmAppDrawFinal` | absent | No declaration. |
| `sead::BtmRootDraw` | absent | No declaration. |
| `sead::BtmSysDraw` | absent | No declaration. |
| `sead::ForegroundBucket` | related only | Reference has `ForegroundBucketMgr`; no `ForegroundBucket` class. |
| `sead::GameConfig` | absent | No `GameConfig` class; target-side configuration integration. |
| `sead::GameConfig::mHeap` | member string | Member name appears in unrelated classes; no `GameConfig` owner. |
| `sead::GameConfig::mWorkHeap` | member string | Member name appears in an unrelated AGL class; no `GameConfig` owner. |
| `sead::MainThread` | absent | `ThreadMgr::getMainThread()` exists; no `MainThread` class. |
| `sead::MicConnectThread` | absent | No declaration; likely target-side microphone integration. |
| `sead::RootCalc` | absent | No declaration. |
| `sead::SysCalc` | absent | No declaration. |
| `sead::SystemManagers` | absent | Only an identifier in `seadGameFramework.cpp`; no class declaration. |
| `sead::TopAppDraw` | absent | No declaration. |
| `sead::TopAppDrawFinal` | absent | No declaration. |
| `sead::TopRootDraw` | absent | No declaration. |
| `sead::TopSysDraw` | absent | No declaration. |

The target's source-path strings show a game-local `Lib/Sead` integration. The
`AppCalc`, `Top*`/`Btm*` draw tasks, `GameConfig`, and thread subclasses should
therefore be treated as target-owned types built around SEAD, not as missing
upstream classes. Their base-class relationships are hypotheses until checked
against target RTTI or call sites.

## AGL

The target has 12 `agl::` strings. Six are exact classes in the Cafe-era AGL
reference under `packages/agl`:

| Target | Reference | Notes |
|---|---|---|
| `agl::detail::RootNode` | `packages/agl/include/detail/aglRootNode.h` | Exact class. |
| `agl::detail::ShaderHolder` | `packages/agl/include/detail/aglShaderHolder.h` | Exact class. |
| `agl::driver::GX2Resource` | `packages/agl/include/detail/aglGX2.h` | Exact class. |
| `agl::lyr::Renderer` | `packages/agl/include/layer/aglRenderer.h` | Exact class. |
| `agl::utl::DynamicTextureAllocator` | `packages/agl/include/utility/aglDynamicTextureAllocator.h` | Exact class. |
| `agl::utl::PrimitiveTexture` | `packages/agl/include/utility/aglPrimitiveTexture.h` | Exact class. |

The other six are not exact class matches:

| Target | Classification | Reference finding |
|---|---|---|
| `agl::Renderer` | marker | The target strings are `agl::Renderer(color)` and `agl::Renderer(depth)`; the class is `agl::lyr::Renderer`. |
| `agl::DrawContextMgr` | absent | No declaration in the available AGL reference. |
| `agl::DynamicTextureAllocator` | namespace-shifted | Reference declares `agl::utl::DynamicTextureAllocator`; do not assume the unqualified name is the same symbol. |
| `agl::Framework` | absent | No declaration in `packages/agl`. |
| `agl::PrivateResource` | namespace-shifted | Reference declares `agl::detail::PrivateResource`; target string omits `detail`. |
| `agl::WorkHeap` | absent | No declaration in the available AGL reference. |

The exact AGL classes have reference-side `static_assert` sizes, including
`GX2Resource` at `0x80`, `Renderer` at `0xF78`, `DynamicTextureAllocator` at
`0x247C`, and `PrimitiveTexture` at `0x11F4`. Those are properties of the
reference snapshot, not measurements of `Block.elf`. A second target-side scan
found no pointer or relocation to an AGL class string usable as typeinfo, no
target AGL vtable identification, and no constructor allocation matching
`0xF78`, `0x247C`, or `0x11F4`. The direct string references are resource or framework task setup,
not allocation sites, so all four target sizes remain unverified; see
[`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md).

`agl::Framework`, `agl::WorkHeap`, and `agl::DrawContextMgr` are plausible
target-side framework/heap integration points. Their absence from the reference
means there is no source-backed layout to import for them.

## FFL

The target carries the `FFL_1_5_6` tag. The available reference is FFL `1.3.10`,
so the version gap is significant. The target string set has 26 raw identifiers,
including version and resource names. Four are exact C++ classes in the older
reference:

| Target | Reference | Scope |
|---|---|---|
| `FFLiAllocatorInterface` | `include/nn/ffl/detail/FFLiAllocatorInterface.h` | Allocation interface. |
| `FFLiBufferAllocatorForZlib` | `include/nn/ffl/detail/FFLiBufferAllocatorForZlib.h` | Zlib buffer allocator. |
| `FFLiZlibInflator` | `include/nn/ffl/FFLiZlibInflator.h` | Zlib inflater. |
| `FFLiZlibInterface` | `include/nn/ffl/FFLiZlibInterface.h` | Zlib interface. |

These four matches are low-level allocation and decompression interfaces. They do
not establish any public FFL rendering, model, or resource class layout.

The following target names are not declared as classes in FFL 1.3.10:

- `FFLDraw` and `FFLHeapDL`: target strings near draw/display-list code; no
  1.3.10 class declaration.
- `FFLResource`: target string for the resource family; 1.3.10 has resource
  types but no class declaration with this spelling.
- `ffl::HeapBufferDL`: lowercase `ffl` namespace; no matching declaration.
- `FFLBodyRes`, `FFLBodyShader`, `FFLResMiddle.dat`, `FFLResHigh.dat`,
  `FFLResMiddleLG.dat`, and `FFLResHighLG.dat`: target resource names.
- `FFL_Hat`, `FFL_HeadTop`, `FFL_HeadFront`, `FFL_HeadSideRight`,
  `FFL_HeadSideLeft`, `FFL_HDB`, `FFL_ODB`, and `FFL_ODB_OLD`: target resource
  or part identifiers.
- `ffl_icon_with_body_depth` and `ffl_simple`: lowercase asset names, not class
  names.

The `FFLResource%03d` string is a path template, not a class declaration. The
1.5.6 resource names must remain target-specific. Do not assume that a 1.3.10
resource header or structure is byte-compatible with the target.

## GSys

No public GSys decompilation was found. The target provides 18 strings and 23
occurrences, all target-specific:

| Symbol | Occurrences | Role / note |
|---|---:|---|
| `gsys::SystemTask` | 1 | Root system task. |
| `gsys::SystemTask::PreCalc` | 1 | Lifecycle phase. |
| `gsys::SystemTask::DrawTV` | 1 | TV render phase. |
| `gsys::SystemTask::PostDrawTV` | 1 | TV post-render phase. |
| `gsys::SystemTask::DrawDRC` | 1 | GamePad render phase. |
| `gsys::SystemTask::PostDrawDRC` | 1 | GamePad post-render phase. |
| `gsys::SystemTask::PostCalc` | 1 | Post-calc phase. |
| `gsys::SystemTask::preCalc_` | 1 | Internal pre-calc member. |
| `gsys::SystemTask::createResource` | 2 | Resource creation path. |
| `gsys::Model` | 1 | Model object. |
| `gsys::Debug` | 1 | Debug object. |
| `gsys::ParticleMgr` | 1 | Particle manager. |
| `gsys::Layer3D` | 1 | 3D layer. |
| `gsys::DrawObj` | 1 | Draw object. |
| `gsys::RenderBuffer::depth` | 1 | Depth buffer member. |
| `gsys::RenderBuffer::color` | 4 | Color buffer members/variants. |
| `gsys::RenderBufferContext::Depth` | 1 | Depth context variant. |
| `gsys::RenderBufferContext::NLD` | 2 | NLD context variants. |

The lifecycle order is directly evidenced by the `SystemTask` strings:
`PreCalc`, `DrawTV`, `PostDrawTV`, `DrawDRC`, `PostDrawDRC`, `PostCalc`. The
resource side is visible through `System/GSys/gsys_resource_`, `.gsysefx`,
`.bgsysdclao`, and the `gsys_areaenv_*`, `gsys_depth_shadow*`, `gsys_gbuffer_*`,
and `gsys_material*` names.

The target constructor candidate at `0x0294377C` makes this more concrete. It
allocates `0x364` bytes, passes `gsys::SystemTask` to the `0x02783658` base
constructor, and builds six `0x54`-byte method-tree entries starting at `+0x7C`.
The six name pointers are at `+0x90`, `+0xE4`, `+0x138`, `+0x18C`, `+0x1E0`,
and `+0x234`; the corresponding delegate entry points are recorded in
[`config/gsys_methods.tsv`](../config/gsys_methods.tsv). This is a target-side
layout skeleton and entry-point map, not a reconstruction. No GSys source was
added to `src/`; method bodies and typed field offsets still require matched
functions. The full entry table is in
[`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md).

## Layout status

The target-side layout pass has moved the boundary for SEAD. `ControllerMgr` at
`0xE8` is directly verified by its allocation and class-name reference.
`TaskBase` at `0x74` and `CalculateTask` at `0xC8` are supported by the
constructor chain and exact reference-size agreement, though their names are
inferred. `TaskMgr` is now target-verified at `0x1A4`; its final method-tree
node occupies `+0x150..+0x1A3`, and the reference's extra trailing fields are
not present in this build.

AGL still has no target constructor or size evidence. Reference headers contain
useful assertions such as `agl::driver::GX2Resource` at `0x80`,
`agl::lyr::Renderer` at `0xF78`, `agl::utl::DynamicTextureAllocator` at
`0x247C`, and `agl::utl::PrimitiveTexture` at `0x11F4`, but those describe the
reference snapshot only. The same applies to `sead::ThreadMgr` at `0x28` and
`FFLiZlibInflator` at `0x44`.

GSys now has a target-backed constructor skeleton, but not a byte-matched
class. The `0x364` object and six method-tree entries are evidence for field
mapping; they are not a declaration or a method body. The audit still changes
no reconstructed source and adds no row to `src/functions.tsv`. A future layout
claim must cite target disassembly or a matched function, especially where the
reference is a different version or branch.

## Practical conclusions

- Use SEAD/AGL headers for class and method names, not for assumed target
  sizes. The SEAD constructor sizes and the `gsys::SystemTask` allocation in
  [`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md) are target-backed; the AGL
  sizes are still reference-only.
- Treat target-only SEAD task/thread classes and AGL framework/heap classes as
  local integration points.
- Use only the four named FFL allocator/zlib interfaces from 1.3.10, and keep all
  1.5.6 resource handling target-specific.
- Use NW4F 1.14.8 headers for naming, while treating the target's 1.14.5 code
  and binary formats as authoritative.
- Use NEX protocol references for wire semantics and method names, not for C++
  object layout.
- Keep GSys target-specific; the lifecycle names plus the `0x364` constructor
  skeleton are the current evidence boundary, not a source layout.
