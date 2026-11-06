#!/usr/bin/env python3
"""Index namespace-qualified RTTI and source strings from the local string dump.

The input is the gitignored `asm/strings.txt` produced from Block.elf.  The
output is a public, path-free table of symbols and line numbers.  A hit is not
proof of a class layout: template arguments, member names and source strings
are all mixed into the same dump.

Usage:
    python tools/rtti_index.py
    python tools/rtti_index.py --input asm/strings.txt --output config/rtti_classes.tsv
"""

from __future__ import annotations

import argparse
import collections
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
INPUT = ROOT / "asm" / "strings.txt"
OUTPUT = ROOT / "config" / "rtti_classes.tsv"

# Order matters only for readability; the regex is namespace-prefixed so these
# do not overlap.  `nw::snd` is the one NintendoWare namespace with a readable
# target string; the rest of NW4F is reached through the 1.14.8 headers.
PREFIXES = ("nn::nex", "sead", "agl", "gsys", "nw::snd")
SYMBOL_RE = re.compile(
    r"(?:" + "|".join(re.escape(prefix) for prefix in PREFIXES) + r")"
    r"(?:::[A-Za-z_][A-Za-z0-9_]*)+"
)


def namespace_of(symbol: str) -> str:
    if symbol.startswith("nn::nex::"):
        return "nn::nex"
    if symbol.startswith("nw::snd::"):
        return "nw"
    return symbol.split("::", 1)[0]


def parse(path: Path):
    records: dict[str, dict] = {}
    total_matches = 0
    with path.open("r", encoding="utf-8", errors="replace") as handle:
        for line_number, line in enumerate(handle, 1):
            for match in SYMBOL_RE.finditer(line):
                symbol = match.group(0)
                total_matches += 1
                record = records.setdefault(
                    symbol,
                    {
                        "namespace": namespace_of(symbol),
                        "symbol": symbol,
                        "owner": symbol.rsplit("::", 1)[0],
                        "leaf": symbol.rsplit("::", 1)[1],
                        "templated": 0,
                        "occurrences": 0,
                        "first_line": line_number,
                    },
                )
                record["occurrences"] += 1
                if match.end() < len(line) and line[match.end()] == "<":
                    record["templated"] = 1
    return records, total_matches


def write_tsv(path: Path, records: dict[str, dict]):
    fields = [
        "namespace",
        "symbol",
        "owner",
        "leaf",
        "templated",
        "occurrences",
        "first_line",
    ]
    rows = sorted(
        records.values(),
        key=lambda row: (row["namespace"], -row["occurrences"], row["symbol"]),
    )
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write("\t".join(fields) + "\n")
        for row in rows:
            handle.write("\t".join(str(row[field]) for field in fields) + "\n")
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, default=INPUT)
    parser.add_argument("--output", type=Path, default=OUTPUT)
    args = parser.parse_args()

    if not args.input.is_file():
        raise SystemExit(
            f"missing {args.input}; generate the local string dump first "
            "(the file is intentionally gitignored)"
        )

    records, total_matches = parse(args.input)
    rows = write_tsv(args.output, records)

    per_namespace = collections.Counter(row["namespace"] for row in rows)
    per_occurrence = collections.Counter()
    for row in rows:
        per_occurrence[row["namespace"]] += row["occurrences"]

    print(
        f"scanned={args.input} matches={total_matches} "
        f"unique={len(rows)} output={args.output}"
    )
    for namespace in PREFIXES:
        key = "nw" if namespace == "nw::snd" else namespace
        print(
            f"  {namespace:8s} unique={per_namespace.get(key, 0):4d} "
            f"occurrences={per_occurrence.get(key, 0):4d}"
        )
    print("top 20:")
    for row in sorted(rows, key=lambda item: (-item["occurrences"], item["symbol"]))[:20]:
        print(
            f"  {row['occurrences']:4d}  {row['namespace']:8s} {row['symbol']}"
        )


if __name__ == "__main__":
    main()
