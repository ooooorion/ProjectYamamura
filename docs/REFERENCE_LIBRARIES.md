# Reference libraries and component versions

This document maps the middleware embedded in `Block.elf` and the external
decompilations that are useful for naming and structure. It is not a build
recipe: no SDK, compiler, game asset, or external decompilation code is
redistributed in this repository.

## Target build

| Component | Version | Evidence |
|---|---|---|
| Cafe SDK | `2.12.13` | Reported by the retail executable; see [`EXTRACTION.md`](EXTRACTION.md). |
| Green Hills compiler | MULTI `5.3.27` | Recorded in the [repository README](../README.md). |
| NintendoWare for Cafe (NW4F) | `1.14.5` | Embedded component tags for `fnt`, `lyt`, `sfnt`, `eft`, and `snd`. |
| NEX | `3.8.3` | Embedded tags `NEX_3_8_3AMA`, `NEX_MM_3_8_3`, and `NEX_DS_3_8_3`. |
| FFL (Face Library) | `1.5.6` | Embedded `FFL_1_5_6` tag. |
| Error library | `2.4.0` | Embedded `Error_2_4_0` tag and the `erreula` runtime library. |
| Software keyboard | `2.4.1` | Embedded `SWKBD_2_4_1` tag and the `swkbd` runtime library. |
| IJG JPEG | untagged | Embedded `IJG:JPEG_Library` tag only. |
| AGL | untagged | `agl::` class/string evidence and AGL resource names; no version tag found. |
| SEAD | untagged | `sead::` class/string evidence and source-path strings; no version tag found. |
| GSys | untagged | `gsys::` strings, `System/GSys/` resources, and tooling references. |

NW4F is statically linked into the executable; it is not one of the RPL
imports. The tags above are component markers, not proof that a public package
with the same version is byte-identical to the linked code.

## External references

| Reference | Version / scope | Match against target | Suggested use |
|---|---|---|---|
| NintendoWare for Cafe package | `1.14.8`, Cafe SDK `2.13.01`, GHS `5.3.25` | Newer than the target's NW4F `1.14.5` / SDK `2.12.13` | API docs and headers for `Sys`, `G3d`, `Lyt`, `Eft`, `Snd`, and `Scfont`. It contains no `GSys`, `AGL`, `SEAD`, or `FFL`. Do not link its static libraries or assume resource-format identity. |
| [FFL decompilation](https://github.com/aboood40091/ffl) | `1.3.10`, from NSMBU `1.3.0` | Older than the target's `1.5.6` | Mii data structures, FFL resource concepts, and allocation interfaces. Verify APIs and resource variants against the target. |
| [SEAD decompilation](https://github.com/aboood40091/sead) | NSMBU-era, with Cafe-specific code | Same family, version untagged | `sead::` class names and layout hypotheses; verify sizes against the target. Its [`packages/agl`](https://github.com/aboood40091/sead/tree/master/packages/agl) is the Wii U/Cafe AGL reference. |
| [AGL decompilation](https://github.com/open-ead/agl) | Switch/NVN branch | Not the target's `GX2` implementation | Shared AGL API and utility concepts only. The current tree uses `aglNVNMgr`, not the Cafe `GX2` driver. |
| [Pretendo NEX](https://github.com/PretendoNetwork/nex) | Current Go protocol implementations | Protocol layer, not the NEX `3.8.3` C++ client | RMC method IDs, wire types, and protocol names for annotating `nn::nex` RTTI. |
| [nex-go](https://github.com/PretendoNetwork/nex-go) | Current | Transport/protocol reference | PRUDP/NEX packet behavior; not a source for `nn::nex` class layouts. |
| [nex-protocols-go](https://github.com/PretendoNetwork/nex-protocols-go) | Current | Protocol definitions | Protocol and method naming; useful for mapping NEX imports and RTTI. |
| [nex-protocols-common-go](https://github.com/PretendoNetwork/nex-protocols-common-go) | Current | Common protocol behavior | Higher-level method semantics for authentication, matchmaking, datastore, and related services. |
| [NintendoSDK-NEX](https://github.com/open-ead/NintendoSDK-NEX) | Switch `4.1.2-apprs` | Different platform and version | Optional cross-reference for NEX class naming, not an exact match. |
| [libjpeg mirror](https://github.com/freedesktop-unofficial-mirror/libjpeg/tree/master) | Generic IJG libjpeg | Target version unknown | JPEG decoder behavior only. The target exposes no JPEG library version. |
| GSys | No public decompilation found | None | Reconstruct from the target's `gsys::` class-name evidence, call sites, and `System/GSys/` resources. |

The NW4F archive's own release notes are relevant to the version gap. The
1.14.6-1.14.7 window includes non-backward-compatible G3d and Lyt binary-format
changes, so 1.14.8 documentation can describe newer resource layouts than the
target's 1.14.5 assets. Treat the package as a naming and API reference, not as
a format specification for this build.

## Target-side indexes

- [`RTTI_INDEX.md`](RTTI_INDEX.md) lists the namespace-qualified target symbol
  strings and their occurrence counts.
- [`MIDDLEWARE_AUDIT.md`](MIDDLEWARE_AUDIT.md) records the name-level matches
  against the SEAD, AGL, FFL, NW4F, NEX, and GSys references, including the
  remaining layout gaps.
- [`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md) records the target-backed
  constructor and size evidence, separate from reference assertions.
- [`config/rtti_classes.tsv`](../config/rtti_classes.tsv) is the machine-readable
  index generated by [`tools/rtti_index.py`](../tools/rtti_index.py) from the local
  ignored string dump; [`config/target_layouts.tsv`](../config/target_layouts.tsv)
  is the equivalent layout evidence table, and
  [`config/gsys_methods.tsv`](../config/gsys_methods.tsv) records the six
  `SystemTask` entry points.

## Dynamic module inventory

The executable has 25 `.fimport_*`/`.dimport_*` sections covering 22 distinct
modules. `coreinit`, `nn_act`, and `nn_boss` also have `.dimport` sections.

| Module | Imported calls | Notes |
|---|---:|---|
| `coreinit` | 157 | Core OS, memory, threads, and runtime support. |
| `gx2` | 142 | GX2 graphics API. |
| `snd_core` | 61 | Core audio. |
| `nn_olv2.rpl` | 57 | OLV online service. |
| `padscore` | 31 | Controller input. |
| `nsysnet` | 25 | Sockets and network support. |
| `nn_boss` | 20 | BOSS background service. |
| `nn_act` | 19 | Account service. |
| `vpad` | 12 | GamePad input. |
| `nn_save` | 11 | Save data. |
| `nlibcurl` | 10 | HTTP via Nintendo's libcurl port. |
| `nn_nfp` | 9 | NFC service. |
| `mic` | 8 | Microphone. |
| `nn_fp` | 7 | FP service. |
| `nn_ac` | 7 | AC service. |
| `proc_ui` | 5 | Process UI. |
| `nn_ndm` | 4 | NDM service. |
| `zlib125` | 3 | zlib 1.2.5. |
| `sysapp` | 3 | System application control. |
| `nn_acp` | 2 | ACP service. |
| `vpadbase` | 1 | GamePad base library. |
| `snd_user` | no index entries | Section present; no imported calls in the current index. |

`erreula.rpl` and `swkbd.rpl` are acquired at runtime through
`OSDynLoad_Acquire` and are not `.fimport` sections. `nn_olv2.rpl` is both an
import module and a runtime-loaded library. Call counts come from the local
`asm/imports_by_name.tsv` index and are useful for prioritisation only.

## Resource formats

The executable references these families. Counts are line occurrences in the
string inventory, not unique assets.

| Family | Examples | Approximate count |
|---|---|---:|
| SZS/SARC archives | `.szs`, `.sarc` | 51 `.szs`, 1 `.sarc` |
| Message text | `.msbt` | 76 |
| Game packs | `.pack` | 24 |
| Models | `.bfres` | 3 |
| Layouts and animation | `.bflyt`, `.bflan` | 3, 1 |
| Audio | `.bfsar`, `.bfwav`, `.bars` | 1, 2, 3 |
| Fonts | `.bffnt` | 1 |
| Shaders and textures | `.gsh`, `.gtx` | 7, 1 |
| Sound configuration | `.bccst`, `.bshst`, `.bagst`, `.bdrcs` | 1 each |
| Game data/configuration | `.dat`, `.cdt`, `.xml` | 12, 2, 4 |
| AGL/GSys resources | `.bagl*`, `.agl*`, `.gsysefx`, `.bgsysdclao` | many |
| FFL resources | `System/FFL/FFLBodyRes.dat`, `FFLBodyShader.gsh`, `FFLResMiddle/High(.LG).dat` | target-specific |

Paths such as `Shader/`, `Model/`, and `Layout/` are content namespaces under
the extracted RPX content root, not SDK installation directories or separate
modules. In the current extraction, the visible top-level content directories
are `Course/`, `CourseThumbnail/`, `Font/`, `Layout/`, `Message/`, `Model/`,
`Pack/`, `Sound/`, and `System/`; strings also reference `Shader/`, `Effect/`,
`Env/`, and `Debug/`, which may be packed or created at runtime.
`System/Agl/agl_resource_` and `System/GSys/gsys_resource_` are middleware
resource-pack prefixes within that content namespace, while `System/FFL/`
contains Face Library data. These are runtime paths under `/vol/content`, not
library names and not evidence of separate SDK components.

## GSys

No public GSys decompilation was found. The target still provides a useful
skeleton:

- `gsys::SystemTask` with `PreCalc`, `DrawTV`, `PostDrawTV`, `DrawDRC`,
  `PostDrawDRC`, and `PostCalc`
- `gsys::Model`, `gsys::Debug`, `gsys::ParticleMgr`, `gsys::Layer3D`,
  `gsys::RenderBuffer`, `gsys::RenderBufferContext`, and `gsys::DrawObj`
- `System/GSys/gsys_resource_`, `.gsysefx`, `.bgsysdclao`, and a large set of
  `gsys_areaenv_*`, `gsys_depth_shadow*`, `gsys_gbuffer_*`, and
  `gsys_material*` names

GSys is adjacent to AGL in the first-party engine stack, not part of NW4F. Its
class and resource map has to come from the target binary. The constructor
candidate at `0x0294377C` allocates `0x364` bytes and registers six
`0x54`-byte method-tree entries at `+0x7C`; the entry points are
`0x0294525C`, `0x029459C8`, `0x02946B14`, `0x02946CCC`, `0x02946D70`, and
`0x02946E0C`. The target layout table, [`config/gsys_methods.tsv`](../config/gsys_methods.tsv),
and [`LAYOUT_VERIFICATION.md`](LAYOUT_VERIFICATION.md) record the details. Do not
expect the NW4F package to fill this gap.

## Rules for using these references

- Use external decompilations for names, data-model hypotheses, and protocol
  semantics. Do not copy their code into `src/`; they are separate projects
  with their own licensing.
- Never commit SDK headers, static libraries, compiler files, or extracted SDK
  trees. The local NW4F package is a read-only reference.
- Verify every proposed class layout or signature against the target before it
  affects a matched function.
- Treat NEX protocol method IDs as useful evidence, but not as proof of C++
  class layout.
- Treat the NW4F 1.14.8 package as newer documentation. The target is 1.14.5,
  and the intervening releases changed G3d/Lyt binary formats.
- For AGL, prefer the Cafe code under `aboood40091/sead/packages/agl`; the
  standalone `open-ead/agl` tree is the Switch/NVN branch.
- For GSys, there is no upstream source to mirror; build a target-specific map
  from class-name evidence, call sites, and resource names.

## Work status

Completed in the target-side pass:

- Built the target RTTI/string index for `nn::nex`, `sead::`, `agl::`, `gsys::`,
  and `nw::snd`; see [`RTTI_INDEX.md`](RTTI_INDEX.md).
- Compared the Wii U SEAD/AGL names with the Cafe-era reference. Six SEAD and
  six AGL classes have exact declarations; aliases, markers, and target-only
  classes are recorded in [`MIDDLEWARE_AUDIT.md`](MIDDLEWARE_AUDIT.md).
- Compared the FFL 1.3.10 reference with the target's `1.5.6` evidence. Only four
  low-level allocator/zlib classes agree; the 1.5.6 resource names remain
  target-specific.
- Recovered the target `.data` and relocation sections from a local RPX and
  checked the middleware class strings for typeinfo/vtable references. The
  strings are not proven RTTI names.
- Verified the `sead::ControllerMgr` constructor size at `0xE8`; the
  `TaskBase` (`0x74`) and `CalculateTask` (`0xC8`) constructor chain also matches
  the reference. `sead::TaskMgr` is target-verified at `0x1A4`; its final
  `MethodTreeNode` occupies `+0x150..+0x1A3`, and the reference's trailing
  `0x1A8` fields are absent.
- Recorded the GSys `SystemTask` constructor skeleton at `0x0294377C`: a
  `0x364`-byte object with six `0x54`-byte method-tree entries, plus their six
  target entry points in [`config/gsys_methods.tsv`](../config/gsys_methods.tsv).
  There is still no byte-matched GSys source.
- Rechecked AGL for a target constructor or vtable. The class strings have no
  pointer/relocation support, and the distinctive reference sizes `0xF78`,
  `0x247C`, and `0x11F4` are not allocation immediates in the target. AGL
  remains reference-only.
- Cross-checked the NW4F `TaskThread` header. The 1.14.8 class is
  `nw::snd::internal::TaskThread`, while the target string is
  `nw::snd::TaskThread`, so this is a leaf-level match only.

Remaining verification work:

1. Extend target class-size and field-offset verification. `ControllerMgr` and
   `TaskMgr` are verified; the AGL sizes remain reference-only. The six GSys
   entry points are recovered, but their bodies are not byte-matched.
   Reference `static_assert` sizes are not target measurements.
2. Resolve target-only SEAD task/thread classes and AGL framework/heap classes
   from target call sites before proposing layouts.
3. Use the NW4F 1.14.8 headers to name static NintendoWare functions, but keep
   the target's 1.14.5 version and binary formats authoritative.
4. Reconstruct GSys method bodies only after a target-side function match; keep
   unsupported methods unnamed.
