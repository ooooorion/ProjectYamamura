#!/usr/bin/env python3
"""Extract one function from asm/main.s in a form m2c can parse.

objdump output is not m2c input: branch targets are bare hex numbers, every
import call carries a bogus <curl_easy_cleanup-0x...> annotation, and there are
no labels. This slices an address range, relabels branches, and optionally runs
m2c on the result.

    python tools/fn2m2c.py 02061BBC 02061CEC --run

Addresses are inclusive and may be written with or without a 0x prefix.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys

ADDR_RE = re.compile(r"^\s*([0-9a-f]+):\t(.*)$")
SYM_RE = re.compile(r"\s*<[^>]*>\s*$")
TARGET_RE = re.compile(r"(?<=\s)([0-9a-f]{5,8})(?=\s|$)")
CALL_MNEMONICS = {"bl", "bla", "bcl"}
NO_OPERAND = {"bctrl", "blrl", "blr"}

DEFAULT_ASM = os.environ.get("SMM_ASM", "asm/main.s")
DEFAULT_M2C = os.environ.get("M2C", "m2c.py")


def parse_addr(text):
    text = text.strip()
    if text.lower().startswith("0x"):
        text = text[2:]
    return int(text, 16)


def slice_function(path, start, end):
    """Instructions between start and end inclusive; main.s is address-sorted."""
    insns = []
    with open(path, encoding="ascii", errors="replace") as f:
        for line in f:
            m = ADDR_RE.match(line.rstrip("\r\n"))
            if not m:
                continue
            addr = int(m.group(1), 16)
            if addr < start:
                continue
            if addr > end:
                break
            insns.append((addr, SYM_RE.sub("", m.group(2)).strip()))
    return insns


def retarget(text, inside):
    mnemonic = text.split()[0]
    if not mnemonic.startswith("b") or mnemonic in NO_OPERAND:
        return text

    def repl(m):
        addr = int(m.group(1), 16)
        if mnemonic in CALL_MNEMONICS or (mnemonic == "b" and addr not in inside):
            return "func_%08X" % addr
        return ".L%08X" % addr

    return TARGET_RE.sub(repl, text)


def render(insns):
    inside = {a for a, _ in insns}
    first = insns[0][0]
    out = ["func_%08X:" % first]
    for addr, text in insns:
        if addr != first:
            out.append(".L%08X:" % addr)
        out.append("    " + retarget(text, inside))
    return "\n".join(out) + "\n", "func_%08X" % first


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Slice a function out of main.s and (optionally) decompile it with m2c.")
    ap.add_argument("start", help="first address, e.g. 02061BBC")
    ap.add_argument("end", help="last address, inclusive")
    ap.add_argument("--asm", default=DEFAULT_ASM, help="listing to slice")
    ap.add_argument("--out", help="output .s (default: next to the listing)")
    ap.add_argument("--m2c", default=DEFAULT_M2C, help="path to m2c.py")
    ap.add_argument("-t", "--target", default="ppc", help="m2c target (default: ppc)")
    ap.add_argument("--run", action="store_true", help="run m2c on the result")
    args = ap.parse_args(argv)

    start, end = parse_addr(args.start), parse_addr(args.end)
    insns = slice_function(args.asm, start, end)
    if not insns:
        print("no instructions in %08X..%08X -- wrong section, or end before start"
              % (start, end))
        return 1

    source, label = render(insns)
    out = args.out or os.path.join(os.path.dirname(args.asm), label.lower() + ".s")
    with open(out, "w", newline="\n", encoding="ascii") as f:
        f.write(source)
    print("%d instructions %08X..%08X -> %s"
          % (len(insns), insns[0][0], insns[-1][0], out))

    if not args.run:
        return 0
    if not os.path.exists(args.m2c):
        print("m2c not found: %s (pass --m2c)" % args.m2c)
        return 1
    return subprocess.call([sys.executable, args.m2c, "-t", args.target, "-f", label, out])


if __name__ == "__main__":
    sys.exit(main())
