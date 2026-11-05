# Provenance

Where every target byte came from, and what was done to it.

## Source

- Title: Super Mario Maker, Wii U, USA (revision 5, v16)
- Title ID: `00050000-1018DC00`
- Copy: legally obtained by the author
- The executable was decrypted and extracted locally; no key, disc image, or
  extracted data is included in this repository.

## Chain

1. The author's own copy was decrypted locally; no key or disc image is included.
2. The main RPX was extracted and converted to ELF with wiiurpxtool.
3. The ELF was repaired to a loadable image.
4. Import calls indexed from `.rela.text`, then labelled in Ghidra (594
   functions, 8,704 call sites).
5. Functions sliced from the listing, decompiled, and matched against the
   repaired ELF.

## Measured artefacts

| Section | VMA | Size |
|---|---|---|
| `.text` | `0x02000020` | `0x00C6E278` |
| `.rodata` | `0x10000000` | `0x00181034` |
| `.data` | `0x10181040` | `0x0002784C` |
| `.bss` | `0x101A9000` | `0x001A3978` |

- `Block.elf`: 20,927,360 bytes
- Import stubs: 594 functions at `0x02C6E2A8`, size `0x8DE0` (created by the
  labeler, not present in the file)
- Import call sites: 8,704

## Not redistributed

The disc image, the ELF, the disassembly listing, the extracted data tree, any
decryption key, the Cafe SDK, and the Green Hills toolchain are absent from
this repository by design. `/orig/`, `/asm/`, `/build/` and `/probe/` are ignored.

## Legal

No affiliation with Nintendo. This is a study of a program the author owns, for
documentation and interoperability research. It distributes no part of the
original work.
