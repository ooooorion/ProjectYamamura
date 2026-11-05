#!/usr/bin/env python3
"""Register MATCH rows from one or more batch result files.

Non-matches are archived by tools/archive_near.py. This tool only copies
sources the batch marked exact and appends a row to src/functions.tsv; the full
match harness still has to pass afterward.
"""
from __future__ import annotations

import argparse
import shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build" / "batch"
TABLE = ROOT / "src" / "functions.tsv"


def result_rows(path):
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line or line.startswith("#"):
            continue
        fields = line.split("\t")
        if len(fields) != 9:
            continue
        yield {
            "name": fields[0],
            "start": fields[1],
            "end": fields[2],
            "status": fields[4],
        }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--results", nargs="+", required=True)
    args = parser.parse_args()
    table = TABLE.read_text(encoding="utf-8")
    if not table.endswith("\n"):
        table += "\n"
    known = {
        line.split("\t", 1)[0]
        for line in table.splitlines()
        if line and not line.startswith("#") and "\t" in line
    }
    registered = 0
    skipped = 0
    for result_name in args.results:
        for row in result_rows(Path(result_name)):
            if row["status"] != "MATCH":
                continue
            name = row["name"]
            if name in known:
                skipped += 1
                continue
            source = BUILD / f"{name}.c"
            if not source.is_file():
                raise SystemExit(f"missing exact candidate source: {source}")
            text = source.read_text(encoding="utf-8").replace(
                "m2c valid-syntax first pass; not verified until the bytes match.",
                "m2c valid-syntax output; byte-verified against Block.elf.",
            )
            (ROOT / "src" / f"fn_{row['start']}.c").write_text(
                text, encoding="utf-8", newline="\n"
            )
            table += f"{name}\t{row['start']}\t{row['end']}\tsrc/fn_{row['start']}.c\n"
            known.add(name)
            registered += 1
    TABLE.write_text(table, encoding="utf-8", newline="\n")
    print(f"registered {registered} exact rows; skipped {skipped} already-known rows")


if __name__ == "__main__":
    main()
