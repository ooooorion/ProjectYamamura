#!/usr/bin/env python3
"""Audit Ghidra function boundaries against the bl-target set and tiny samples.

    python tools/audit_boundaries.py

Reads:
  build/ghidra/functions_clean.tsv
  build/ghidra/functions_timeout.tsv
  build/all_bl_targets.txt
  asm/main.s

Writes:
  docs/BOUNDARY_AUDIT.md
  build/ghidra/tiny_samples.tsv
"""
from __future__ import annotations

import argparse
import re
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TEXT_LO = 0x02000020
TEXT_HI = 0x02C6E298
INSN_RE = re.compile(r"^\s*([0-9a-f]+):\s+(.+?)\s*$")


def load_ghidra(path: Path) -> dict[int, dict[str, object]]:
    rows: dict[int, dict[str, object]] = {}
    lines = path.read_text(encoding="utf-8").splitlines()
    header = lines[0].split("\t")
    index = {name: i for i, name in enumerate(header)}
    for line in lines[1:]:
        if not line.strip():
            continue
        fields = line.split("\t")
        if len(fields) < len(header):
            continue
        entry = int(fields[index["entry"]], 16)
        if not (TEXT_LO <= entry <= TEXT_HI):
            continue
        maximum = int(fields[index["max"]], 16)
        rows[entry] = {
            "start": entry,
            "end": max(entry + 4, maximum + 1),
            "body_bytes": int(fields[index["bytes"]]),
            "thunk": int(fields[index["thunk"]]),
            "fragmented": int(fields[index["fragmented"]]),
            "name": fields[index["name"]],
        }
    return rows


def load_bl_targets(path: Path) -> set[int]:
    targets = set()
    for line in path.read_text(encoding="ascii", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        value = int(line, 16)
        if TEXT_LO <= value <= TEXT_HI:
            targets.add(value)
    return targets


def load_exact_starts(path: Path) -> set[int]:
    starts = set()
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        fields = line.split("\t")
        if len(fields) >= 2:
            starts.add(int(fields[1], 16))
    return starts


def select_samples(rows: dict[int, dict[str, object]],
                   exact: set[int]) -> list[dict[str, object]]:
    tiny = sorted(
        (row for row in rows.values() if int(row["body_bytes"]) <= 8),
        key=lambda row: (row["body_bytes"], row["start"]),
    )
    if not tiny:
        return []
    sampled: list[dict[str, object]] = []
    seen: set[int] = set()
    indexes = [0, len(tiny) // 4, len(tiny) // 2, (3 * len(tiny)) // 4,
               len(tiny) - 1]
    for index in indexes:
        row = tiny[index]
        if row["start"] not in seen:
            sampled.append(row)
            seen.add(row["start"])
    for row in tiny:
        if row["start"] in exact and row["start"] not in seen:
            sampled.append(row)
            seen.add(row["start"])
            if len(sampled) >= 12:
                break
    for row in tiny:
        if len(sampled) >= 12:
            break
        if row["start"] not in seen:
            sampled.append(row)
            seen.add(row["start"])
    return sorted(sampled, key=lambda row: row["start"])


def read_sample_instructions(asm: Path,
                             samples: list[dict[str, object]]) -> dict[int, list[str]]:
    wanted: dict[int, int] = {}
    for row in samples:
        start = int(row["start"])
        end = int(row["end"])
        for address in range(start, end, 4):
            wanted[address] = start
    found: dict[int, list[str]] = {int(row["start"]): [] for row in samples}
    with asm.open(encoding="ascii", errors="replace") as handle:
        for line in handle:
            match = INSN_RE.match(line)
            if not match:
                continue
            address = int(match.group(1), 16)
            owner = wanted.get(address)
            if owner is not None:
                found[owner].append(match.group(2).strip())
    return found


def terminal_verdict(instructions: list[str]) -> str:
    if not instructions:
        return "NO INSTRUCTIONS"
    last = instructions[-1].split()[0]
    if last == "blr":
        return "ends blr"
    if last in ("b", "ba"):
        return "tail branch"
    if last == "bctr":
        return "tail via bctr"
    if last == "nop":
        return "nop only"
    return f"unexpected terminal: {last}"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ghidra", default="build/ghidra/functions_clean.tsv")
    parser.add_argument("--old", default="build/ghidra/functions_timeout.tsv")
    parser.add_argument("--bl-targets", default="build/all_bl_targets.txt")
    parser.add_argument("--exact", default="src/functions.tsv")
    parser.add_argument("--asm", default="asm/main.s")
    parser.add_argument("--log", default="build/ghidra/export_clean.log")
    parser.add_argument("--out", default="docs/BOUNDARY_AUDIT.md")
    parser.add_argument("--samples-out", default="build/ghidra/tiny_samples.tsv")
    args = parser.parse_args()

    clean = load_ghidra(ROOT / args.ghidra)
    old = load_ghidra(ROOT / args.old)
    bl_targets = load_bl_targets(ROOT / args.bl_targets)
    exact = load_exact_starts(ROOT / args.exact)
    clean_starts = set(clean)
    old_starts = set(old)
    samples = select_samples(clean, exact)
    instructions = read_sample_instructions(ROOT / args.asm, samples)
    log_text = (ROOT / args.log).read_text(encoding="utf-8", errors="replace")

    common = clean_starts & old_starts
    changed = sum(clean[start]["end"] != old[start]["end"] for start in common)
    missing_bl = sorted(bl_targets - clean_starts)
    ghidra_only = sorted(clean_starts - bl_targets)
    missing_exact = sorted(exact - clean_starts)
    tiny_all = [row for row in clean.values() if int(row["body_bytes"]) <= 8]
    tiny_4 = [row for row in tiny_all if int(row["body_bytes"]) == 4]
    missing_insns = read_sample_instructions(
        ROOT / args.asm,
        [{"start": start, "end": start + 4} for start in missing_bl],
    )
    missing_lines = []
    for start in missing_bl:
        insns = missing_insns.get(start, [])
        first = insns[0].split()[0] if insns else "—"
        owners = [
            f"{row['start']:08X}..{int(row['end']) - 1:08X}"
            for row in clean.values()
            if int(row["start"]) < start < int(row["end"])
        ]
        inventory_row = "verified (exact)" if start in exact else "bl-target (untried)"
        missing_lines.append(
            f"| `{start:08X}` | `{first}` | "
            f"{owners[0] if owners else 'none'} | {inventory_row} |"
        )
    row_lines = []
    for row in samples:
        start = int(row["start"])
        insns = instructions.get(start, [])
        terminal = terminal_verdict(insns)
        kind = "exact" if start in exact else "untried"
        row_lines.append(
            f"| `{start:08X}` | {int(row['body_bytes'])} | {int(row['thunk'])} | "
            f"{kind} | `{insns[0].split()[0] if insns else '—'}` | "
            f"`{insns[-1].split()[0] if insns else '—'}` | "
            f"{len(insns)} | {terminal} |"
        )
    sample_file = ROOT / args.samples_out
    sample_file.parent.mkdir(parents=True, exist_ok=True)
    sample_file.write_text(
        "start\tbody_bytes\tthunk\tkind\tfirst\tlast\tinstructions\tverdict\n"
        + "\n".join(
            f"{int(row['start']):08X}\t{int(row['body_bytes'])}\t"
            f"{int(row['thunk'])}\t"
            f"{'exact' if int(row['start']) in exact else 'untried'}\t"
            f"{instructions.get(int(row['start']), [''])[0].split()[0] if instructions.get(int(row['start'])) else ''}\t"
            f"{instructions.get(int(row['start']), [''])[-1].split()[0] if instructions.get(int(row['start'])) else ''}\t"
            f"{len(instructions.get(int(row['start']), []))}\t"
            f"{terminal_verdict(instructions.get(int(row['start']), []))}"
            for row in samples
        )
        + "\n",
        encoding="utf-8",
        newline="\n",
    )

    lines = [
        "# Ghidra boundary audit",
        "",
        f"Generated {date.today().isoformat()} from Ghidra 12.1.2 headless analysis.",
        "",
        "## Clean run",
        "",
        f"- Clean boundary export: **{len(clean):,}** functions",
        f"- Timed-out export: **{len(old):,}** functions",
        f"- Shared starts: **{len(common):,}**",
        f"- Clean-only starts: **{len(clean_starts - old_starts):,}**",
        f"- Timed-out-only starts: **{len(old_starts - clean_starts):,}**",
        f"- Changed end boundaries among shared starts: **{changed:,}**",
        f"- Analysis timeout in clean log: **{'yes' if 'Analysis timed out' in log_text else 'no'}**",
        "",
        "## Cross-check against `bl` targets",
        "",
        f"- Direct `.text` `bl` targets: **{len(bl_targets):,}**",
        f"- Ghidra covered: **{len(bl_targets & clean_starts):,}**",
        f"- `bl` targets absent from Ghidra: **{len(missing_bl):,}**",
        f"- Ghidra-only starts (pointer-reached, thunks, cold blocks): "
        f"**{len(ghidra_only):,}**",
        f"- Exact starts present in Ghidra: **{len(exact & clean_starts):,} / {len(exact):,}**",
        f"- Exact starts absent from Ghidra: **{len(missing_exact):,}**",
        "",
        "### Missing `bl` targets",
        "",
        "These are real direct-call entries that Ghidra did not split into functions. "
        "Four are already verified exact rows; the other five are retained as "
        "untried `bl-target` rows.",
        "",
        "| Start | First instruction | Containing Ghidra body | Inventory row |",
        "|---|---|---|---|",
        *missing_lines,
        "",
        "## Tiny-function sample",
        "",
        f"There are **{len(tiny_all):,}** boundaries with `body_bytes <= 8`, "
        f"including **{len(tiny_4):,}** four-byte boundaries. The sample below is "
        "stratified across the tiny set and includes exact matches.",
        "",
        "| Start | Body bytes | Thunk | Status | First | Last | Insns | Verdict |",
        "|---|---:|---:|---|---|---|---:|---|",
        *row_lines,
        "",
        "## Notes",
        "",
        "- The clean run disables `Stack` before analysis; disassembly, function search, "
        "function creation, and the PowerPC constant-reference analyzer remain enabled.",
        "- A boundary is not proof of semantic correctness. This audit checks "
        "coverage against the branch-target set and verifies that sampled tiny "
        "bodies contain plausible instructions and terminal flow.",
        "- `ghidra_only` starts are expected because Ghidra also finds functions "
        "reached through pointers, thunks, and cold blocks that are not direct "
        "`bl` targets.",
        "",
    ]
    (ROOT / args.out).write_text("\n".join(lines), encoding="utf-8", newline="\n")
    print(f"clean {len(clean):,}; old {len(old):,}; shared {len(common):,}; "
          f"changed {changed:,}")
    print(f"bl {len(bl_targets):,}; covered {len(bl_targets & clean_starts):,}; "
          f"missing {len(missing_bl):,}; ghidra-only {len(ghidra_only):,}")
    print(f"tiny {len(tiny_all):,}; sample {len(samples):,}; "
          f"written {args.out} and {args.samples_out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
