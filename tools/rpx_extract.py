#!/usr/bin/env python3
"""Decompress a local Wii U RPX/RPL into an ELF-like inspection file.

The input is an ELF32 big-endian container. Sections carrying the RPX zlib flag
start with a four-byte uncompressed size followed by one zlib stream. This tool
writes decompressed section payloads and an updated section table so the
repository's read-only ELF helpers can inspect .data, .rodata and relocations.

The output is derived game data. Write it under a gitignored path such as
build/Block.elf; never commit it.

Usage:
    python tools/rpx_extract.py --rpx /path/to/Block.rpx --output build/Block.elf
"""
from __future__ import annotations

import argparse
import struct
import sys
import zlib
from pathlib import Path

SHF_RPL_ZLIB = 0x08000000
SHT_NOBITS = 8
ALIGN = 0x40


def be32(data: bytes, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def extract(rpx: Path, output: Path) -> None:
    data = rpx.read_bytes()
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise SystemExit(f"{rpx}: not a 32-bit big-endian ELF")

    shoff = be32(data, 32)
    shentsize = struct.unpack_from(">H", data, 46)[0]
    shnum = struct.unpack_from(">H", data, 48)[0]
    shstrndx = struct.unpack_from(">H", data, 50)[0]
    if shentsize != 40 or shstrndx >= shnum:
        raise SystemExit(f"{rpx}: unsupported ELF section table")

    sections = [
        list(struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize))
        for i in range(shnum)
    ]
    payloads: list[bytes | None] = []
    for index, section in enumerate(sections):
        typ = section[1]
        flags = section[2]
        offset = section[4]
        size = section[5]
        if typ == SHT_NOBITS or offset == 0:
            payloads.append(None)
            continue
        raw = data[offset:offset + size]
        if flags & SHF_RPL_ZLIB:
            if len(raw) < 4:
                raise SystemExit(f"section {index}: truncated compressed header")
            expected = be32(raw, 0)
            try:
                payload = zlib.decompress(raw[4:])
            except zlib.error as exc:
                raise SystemExit(f"section {index}: zlib: {exc}") from exc
            if len(payload) != expected:
                raise SystemExit(
                    f"section {index}: expected {expected:#x}, got {len(payload):#x}"
                )
            section[5] = expected
            section[2] &= ~SHF_RPL_ZLIB
        else:
            payload = raw
        payloads.append(payload)

    names = payloads[shstrndx]
    if names is None:
        raise SystemExit(f"{rpx}: missing compressed section-name table")

    def section_name(index: int) -> str:
        start = sections[index][0]
        if start >= len(names):
            return "<bad-name-offset>"
        end = names.find(b"\0", start)
        if end < 0:
            end = len(names)
        return names[start:end].decode("ascii", "replace")

    # Keep the original ELF header and section-table location, but place
    # decompressed payloads after the table with their natural alignment.
    image = bytearray(ALIGN)
    cursor = max(ALIGN, shoff + shnum * shentsize)
    image.extend(b"\0" * (cursor - len(image)))
    for section, payload in zip(sections, payloads):
        if payload is None:
            continue
        align = max(1, min(int(section[8]) or 1, 0x1000))
        cursor = (cursor + align - 1) & ~(align - 1)
        if len(image) < cursor:
            image.extend(b"\0" * (cursor - len(image)))
        section[4] = cursor
        image.extend(payload)
        cursor += len(payload)

    image[:0x34] = data[:0x34]
    for index, section in enumerate(sections):
        struct.pack_into(">IIIIIIIIII", image, shoff + index * shentsize, *section)

    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(image)
    print(f"read {rpx} ({len(data)} bytes); wrote {output} ({len(image)} bytes)")
    for index, section in enumerate(sections):
        payload = payloads[index]
        print(
            f"{index:02d} {section_name(index)!r:24} "
            f"addr={section[3]:08X} size={section[5]:08X} "
            f"bytes={0 if payload is None else len(payload):08X}"
        )


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rpx", required=True, type=Path, help="local Block.rpx")
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("build/Block.elf"),
        help="ignored output path (default: build/Block.elf)",
    )
    args = parser.parse_args(argv)
    extract(args.rpx, args.output)
    return 0


if __name__ == "__main__":
    sys.exit(main())
