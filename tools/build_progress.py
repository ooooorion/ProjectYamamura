#!/usr/bin/env python3
"""Build the Ghidra function-boundary inventory and its progress graph.

    python tools/build_progress.py

Inputs:
  build/ghidra/functions_clean3.tsv  Ghidra export from tools/ExportFunctionBoundaries.java
  src/functions.tsv             byte-verified functions
  src/near/                     archived near misses and their README tables

Outputs:
  config/function_boundaries.tsv
  docs/progress.html            self-contained interactive graph
  docs/progress.svg             static graph for GitHub Markdown
"""
from __future__ import annotations

import argparse
import html
import json
import math
import re
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TEXT_LO = 0x02000020
TEXT_HI = 0x02C6E298
BAND_SIZE = 0x10000
COLORS = {
    "exact": "#52d6a3",
    "near": "#ffb45e",
    "untried": "#34435d",
}
BG = "#0c1422"
PANEL = "#121d2e"
TEXT = "#e8eefc"
MUTED = "#91a1bb"
GRID = "#26354c"


@dataclass
class Boundary:
    start: int
    end: int
    name: str
    status: str = "untried"
    source: str = ""
    verified_end: int | None = None
    ghidra_name: str = ""
    body_bytes: int = 0
    ranges: int = 0
    thunk: int = 0
    boundary: str = "ghidra"
    missing_source: int = 0
    note: str = ""


@dataclass
class Band:
    start: int
    exact: int = 0
    near: int = 0
    untried: int = 0

    @property
    def total(self) -> int:
        return self.exact + self.near + self.untried


def hex_addr(value: int) -> str:
    return f"{value:08X}"


def pct(value: int, total: int) -> float:
    return (100.0 * value / total) if total else 0.0


def load_exact(path: Path) -> dict[int, tuple[str, int, str]]:
    exact: dict[int, tuple[str, int, str]] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        fields = line.split("\t")
        if len(fields) < 4:
            continue
        start = int(fields[1], 16)
        # functions.tsv ends are inclusive; the inventory uses exclusive ends.
        exact[start] = (fields[0], int(fields[2], 16) + 4, fields[3])
    return exact


def range_from_header(text: str) -> int | None:
    match = re.search(r"0x([0-9A-Fa-f]{8})\.\.0x([0-9A-Fa-f]{8})", text)
    if not match:
        return None
    return int(match.group(2), 16) + 4


def load_near(root: Path) -> dict[int, dict[str, object]]:
    near: dict[int, dict[str, object]] = {}
    for path in sorted(root.rglob("*.c")):
        match = re.match(r"(?:func|fn)_([0-9A-Fa-f]{8})\.c$", path.name)
        if not match:
            continue
        start = int(match.group(1), 16)
        try:
            header = "\n".join(path.read_text(encoding="utf-8").splitlines()[:2])
        except (OSError, UnicodeDecodeError):
            header = ""
        near[start] = {
            "end": range_from_header(header),
            "source": path.relative_to(ROOT).as_posix(),
            "name": path.stem,
            "missing": 0,
        }

    # Some old shards archived a COMPILE row without copying its generated
    # source. Keep those candidates in the inventory; their range is in the
    # shard README table.
    row_re = re.compile(
        r"^\|\s*`((?:func|fn)_[0-9A-Fa-f]{8})`\s*\|\s*"
        r"`([0-9A-Fa-f]{8})\.\.([0-9A-Fa-f]{8})`\s*\|"
    )
    for readme in sorted(root.glob("*/README.md")):
        for line in readme.read_text(encoding="utf-8").splitlines():
            match = row_re.match(line)
            if not match:
                continue
            name, start_s, end_s = match.groups()
            start = int(start_s, 16)
            if start in near:
                continue
            if (readme.parent / f"{name}.c").exists():
                continue
            near[start] = {
                "end": int(end_s, 16) + 4,
                "source": "",
                "name": name,
                "missing": 1,
            }
    return near


def load_bl_targets(path: Path) -> set[int]:
    targets: set[int] = set()
    if not path.exists():
        return targets
    for line in path.read_text(encoding="ascii", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        value = int(line, 16)
        if TEXT_LO <= value <= TEXT_HI:
            targets.add(value)
    return targets


def load_ghidra(path: Path) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    lines = path.read_text(encoding="utf-8").splitlines()
    if not lines:
        raise SystemExit(f"{path}: empty Ghidra export")
    header = lines[0].split("\t")
    index = {name: i for i, name in enumerate(header)}
    required = {"entry", "min", "max", "bytes", "ranges", "name",
                "thunk", "fragmented"}
    missing = required - set(index)
    if missing:
        raise SystemExit(f"{path}: missing columns: {sorted(missing)}")
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
        rows.append({
            "entry": entry,
            "end": max(entry + 4, maximum + 1),
            "body_bytes": int(fields[index["bytes"]]),
            "ranges": int(fields[index["ranges"]]),
            "ghidra_name": fields[index["name"]],
            "thunk": int(fields[index["thunk"]]),
            "fragmented": int(fields[index["fragmented"]]),
        })
    return rows


def build_inventory(
    ghidra: list[dict[str, object]],
    exact: dict[int, tuple[str, int, str]],
    near: dict[int, dict[str, object]],
    bl_targets: set[int],
) -> list[Boundary]:
    rows: dict[int, Boundary] = {}

    for item in ghidra:
        start = int(item["entry"])
        rows[start] = Boundary(
            start=start,
            end=int(item["end"]),
            name=f"func_{hex_addr(start)}",
            ghidra_name=str(item["ghidra_name"]),
            body_bytes=int(item["body_bytes"]),
            ranges=int(item["ranges"]),
            thunk=int(item["thunk"]),
        )

    for start, (name, verified_end, source) in exact.items():
        if start in rows:
            row = rows[start]
            row.status = "exact"
            row.name = name
            row.source = source
            row.verified_end = verified_end
            if row.end != verified_end:
                row.note = "Ghidra body differs from verified range"
        else:
            rows[start] = Boundary(
                start=start,
                end=verified_end,
                name=name,
                status="exact",
                source=source,
                verified_end=verified_end,
                boundary="verified",
            )

    for start, item in near.items():
        verified_end = item["end"]
        if start in rows:
            row = rows[start]
            row.status = "near"
            row.name = str(item["name"])
            row.source = str(item["source"])
            row.verified_end = int(verified_end) if verified_end else None
            row.missing_source = int(item["missing"])
            if row.end != (row.verified_end or row.end):
                row.note = "Ghidra body differs from archived range"
        else:
            inferred_end = int(verified_end) if verified_end else start + 4
            row = Boundary(
                start=start,
                end=inferred_end,
                name=str(item["name"]),
                status="near",
                source=str(item["source"]),
                verified_end=int(verified_end) if verified_end else None,
                boundary="archive" if verified_end else "archive-unknown",
                missing_source=int(item["missing"]),
            )
            if not verified_end:
                row.note = "no archived range; end needs review"
            rows[start] = row

    # Ghidra can miss a valid direct-call entry point. Keep the branch-target
    # candidate in the inventory, but label the boundary source honestly.
    all_starts = sorted(set(rows) | set(bl_targets))
    for index, start in enumerate(all_starts):
        if start in rows:
            continue
        end = all_starts[index + 1] if index + 1 < len(all_starts) else start + 4
        rows[start] = Boundary(
            start=start,
            end=end,
            name=f"func_{hex_addr(start)}",
            status="untried",
            boundary="bl-target",
            note="direct bl target not returned by Ghidra",
        )

    return sorted(rows.values(), key=lambda row: row.start)


def make_bands(rows: list[Boundary]) -> list[Band]:
    if not rows:
        return []
    first = rows[0].start // BAND_SIZE
    last = (max(row.end for row in rows) - 1) // BAND_SIZE
    bands = {index: Band(index * BAND_SIZE) for index in range(first, last + 1)}
    for row in rows:
        band = bands.get(row.start // BAND_SIZE)
        if band is not None:
            setattr(band, row.status, getattr(band, row.status) + 1)
    return [bands[index] for index in range(first, last + 1)]


def make_stats(rows: list[Boundary], bands: list[Band]) -> dict[str, object]:
    exact = sum(row.status == "exact" for row in rows)
    near = sum(row.status == "near" for row in rows)
    untried = sum(row.status == "untried" for row in rows)
    done = exact + near
    missing_near = sum(row.missing_source for row in rows)
    known_not_ghidra = sum(row.boundary != "ghidra" for row in rows)
    ghidra_count = sum(row.boundary == "ghidra" for row in rows)
    verified_bytes = sum(
        (row.verified_end - row.start) for row in rows
        if row.status == "exact" and row.verified_end is not None
    )
    max_band = max(bands, key=lambda band: band.total) if bands else None
    top_untouched = sorted(
        (band for band in bands if band.untried),
        key=lambda band: (-band.untried, band.start),
    )[:8]
    top_done = sorted(
        (band for band in bands if band.exact + band.near),
        key=lambda band: (-(band.exact + band.near), band.start),
    )[:8]
    return {
        "total": len(rows),
        "exact": exact,
        "near": near,
        "untried": untried,
        "done": done,
        "done_pct": pct(done, len(rows)),
        "exact_pct": pct(exact, len(rows)),
        "near_pct": pct(near, len(rows)),
        "untried_pct": pct(untried, len(rows)),
        "missing_near": missing_near,
        "known_not_ghidra": known_not_ghidra,
        "ghidra_count": ghidra_count,
        "archive_rows": 4937,
        "verified_bytes": verified_bytes,
        "text_start": min(row.start for row in rows),
        "text_end": max(row.end for row in rows),
        "max_band": max_band.total if max_band else 0,
        "top_untouched": top_untouched,
        "top_done": top_done,
        "atlas": "".join(
            {"exact": "E", "near": "N", "untried": "U"}[row.status]
            for row in rows
        ),
    }


def band_title(band: Band) -> str:
    end = band.start + BAND_SIZE - 1
    return (
        f"0x{band.start:08X}–0x{end:08X} · "
        f"{band.exact} exact · {band.near} near · {band.untried} untouched"
    )


def band_svg(bands: list[Band], stats: dict[str, object],
             left: int = 58, top: int = 26, width: int = 1015,
             height: int = 214) -> str:
    max_total = max(1, int(stats["max_band"]))
    bottom = top + height
    bar_step = width / max(1, len(bands))
    bar_width = max(1.0, bar_step - 1.1)
    parts = [
        f'<svg class="band-svg" viewBox="0 0 {left + width + 28} {bottom + 34}" '
        f'role="img" aria-label="Function coverage by 64 KiB address band">',
        f'<title>Function coverage by 64 KiB address band</title>',
        f'<rect x="{left}" y="{top}" width="{width}" height="{height}" '
        f'fill="none"/>',
    ]
    for tick in (0, 0.5, 1.0):
        value = int(round(max_total * tick))
        y = bottom - height * tick
        parts.append(
            f'<line x1="{left}" y1="{y:.2f}" x2="{left + width}" y2="{y:.2f}" '
            f'stroke="{GRID}" stroke-width="1"/>'
        )
        parts.append(
            f'<text x="{left - 10}" y="{y + 4:.2f}" text-anchor="end" '
            f'font-size="11" fill="{MUTED}">{value}</text>'
        )
    for index, band in enumerate(bands):
        x = left + index * bar_step + (bar_step - bar_width) / 2
        y = bottom
        for key in ("exact", "near", "untried"):
            count = getattr(band, key)
            if not count:
                continue
            segment = height * count / max_total
            y -= segment
            parts.append(
                f'<rect x="{x:.2f}" y="{y:.2f}" width="{bar_width:.2f}" '
                f'height="{segment:.2f}" fill="{COLORS[key]}" '
                f'data-status="{key}"><title>{html.escape(band_title(band))}'
                f'</title></rect>'
            )
        if not band.total:
            parts.append(
                f'<rect x="{x:.2f}" y="{bottom - 1}" width="{bar_width:.2f}" '
                f'height="1" fill="{GRID}"/>'
            )
    for index in (0, len(bands) // 2, len(bands) - 1):
        if not bands:
            continue
        band = bands[index]
        x = left + index * bar_step + bar_step / 2
        parts.append(
            f'<text x="{x:.2f}" y="{bottom + 19}" text-anchor="middle" '
            f'font-size="11" fill="{MUTED}">0x{band.start:08X}</text>'
        )
    parts.append("</svg>")
    return "".join(parts)


def donut_svg(stats: dict[str, object]) -> str:
    radius = 54
    circumference = 2 * math.pi * radius
    total = max(1, int(stats["total"]))
    segments = [
        ("exact", int(stats["exact"])),
        ("near", int(stats["near"])),
        ("untried", int(stats["untried"])),
    ]
    offset = 0.0
    circles = [
        f'<circle cx="80" cy="80" r="{radius}" fill="none" '
        f'stroke="#202d42" stroke-width="17"/>'
    ]
    for key, count in segments:
        length = circumference * count / total
        if count:
            circles.append(
                f'<circle cx="80" cy="80" r="{radius}" fill="none" '
                f'stroke="{COLORS[key]}" stroke-width="17" '
                f'stroke-dasharray="{length:.3f} {circumference - length:.3f}" '
                f'stroke-dashoffset="{-offset:.3f}" transform="rotate(-90 80 80)"/>'
            )
        offset += length
    return (
        '<svg class="donut" viewBox="0 0 160 160" role="img" '
        'aria-label="Exact, near and untouched function shares">'
        + "".join(circles)
        + '<text x="80" y="75" text-anchor="middle" fill="' + TEXT
        + '" font-size="23" font-weight="700">'
        + f'{stats["done_pct"]:.1f}%' + '</text>'
        + '<text x="80" y="94" text-anchor="middle" fill="' + MUTED
        + '" font-size="9" letter-spacing="1.3">RECONSTRUCTED</text></svg>'
    )


def table_rows(bands: list[Band], top: bool = False) -> str:
    out = []
    for band in bands:
        done = band.exact + band.near
        out.append(
            "<tr>"
            f"<td><code>0x{band.start:08X}</code></td>"
            f"<td>{band.total}</td>"
            f"<td class=\"exact-text\">{band.exact}</td>"
            f"<td class=\"near-text\">{band.near}</td>"
            f"<td>{band.untried}</td>"
            f"<td>{pct(done, band.total):.0f}%</td>"
            "</tr>"
        )
    return "".join(out)


def render_html(rows: list[Boundary], bands: list[Band],
                stats: dict[str, object]) -> str:
    top_untouched = table_rows(stats["top_untouched"])
    top_done = table_rows(stats["top_done"])
    note = (
        '<p class="note">The older 27,267 count was only direct <code>bl</code> '
        f'targets. This inventory uses Ghidra\'s function manager: '
        f'{stats["ghidra_count"]:,} analyzed boundaries plus '
        f'{stats["known_not_ghidra"]} recorded boundaries. Ghidra also finds '
        'pointer-reached functions, thunks, and cold blocks.</p>'
    )
    if stats["missing_near"]:
        note += (
            f'<p class="note">{stats["missing_near"]} archived near-miss '
            'candidates have no retained generated source; their boundaries '
            'come from the shard README tables.</p>'
        )
    note += (
        f'<p class="note">The archive index has {stats["archive_rows"]:,} rows; '
        f'the graph uses {stats["near"]:,} unique near starts. '
        'The final headless run disabled the Stack analyzer and completed cleanly '
        'in 810 seconds; PowerPC constant-reference analysis remained enabled.</p>'
    )
    data = {
        "total": stats["total"],
        "atlas": stats["atlas"],
        "exact": stats["exact"],
        "near": stats["near"],
        "untried": stats["untried"],
    }
    exact_pct = stats["exact_pct"]
    near_pct = stats["near_pct"]
    untried_pct = stats["untried_pct"]
    return f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="description" content="Project Yamamura function-boundary and decompilation coverage graph">
<title>Project Yamamura · Coverage</title>
<style>
:root {{
  color-scheme: dark;
  --bg: {BG};
  --panel: {PANEL};
  --text: {TEXT};
  --muted: {MUTED};
  --line: {GRID};
  --exact: {COLORS['exact']};
  --near: {COLORS['near']};
  --untried: {COLORS['untried']};
}}
* {{ box-sizing: border-box; }}
body {{
  margin: 0;
  background: radial-gradient(1200px 600px at 15% -10%, #193451 0%, var(--bg) 55%);
  color: var(--text);
  font: 15px/1.5 Inter, ui-sans-serif, system-ui, -apple-system, "Segoe UI", sans-serif;
}}
main {{ max-width: 1180px; margin: 0 auto; padding: 42px 26px 64px; }}
a {{ color: #8dc7ff; }}
.eyebrow {{ color: var(--exact); font-size: 11px; font-weight: 800; letter-spacing: 1.8px; text-transform: uppercase; }}
h1 {{ font-size: clamp(32px, 5vw, 58px); line-height: 1.03; letter-spacing: -2px; margin: 14px 0 12px; max-width: 800px; }}
h1 span {{ color: var(--exact); }}
.lede {{ color: var(--muted); max-width: 780px; font-size: 16px; }}
.meta {{ color: var(--muted); font-size: 12px; margin-top: 18px; }}
.meta code {{ color: #c9d7ea; }}
.kpis {{ display: grid; grid-template-columns: repeat(4, 1fr); gap: 12px; margin: 30px 0 16px; }}
.kpi, .panel {{ background: rgba(18,29,46,.88); border: 1px solid var(--line); border-radius: 14px; }}
.kpi {{ padding: 17px 18px; }}
.kpi .label {{ color: var(--muted); font-size: 10px; font-weight: 800; letter-spacing: 1.3px; text-transform: uppercase; }}
.kpi .value {{ font-size: 30px; font-weight: 800; letter-spacing: -1px; margin: 4px 0 1px; }}
.kpi .sub {{ color: var(--muted); font-size: 12px; }}
.kpi.exact .value {{ color: var(--exact); }}
.kpi.near .value {{ color: var(--near); }}
.kpi.todo .value {{ color: #a8b8cf; }}
.panel {{ padding: 22px; margin-top: 16px; }}
.panel h2 {{ font-size: 16px; margin: 0; letter-spacing: -.2px; }}
.panel .panel-sub {{ color: var(--muted); font-size: 12px; margin-top: 3px; }}
.panel-head {{ display: flex; justify-content: space-between; gap: 20px; align-items: baseline; margin-bottom: 18px; }}
.overview {{ display: grid; grid-template-columns: 180px 1fr; gap: 24px; align-items: center; }}
.donut {{ width: 160px; height: 160px; display: block; }}
.legend {{ display: flex; flex-wrap: wrap; gap: 13px 22px; color: var(--muted); font-size: 12px; margin: 4px 0 20px; }}
.legend span {{ display: inline-flex; align-items: center; gap: 7px; }}
.swatch {{ width: 9px; height: 9px; border-radius: 2px; display: inline-block; }}
.swatch.exact {{ background: var(--exact); }}
.swatch.near {{ background: var(--near); }}
.swatch.untried {{ background: var(--untried); }}
.progress {{ display: flex; height: 16px; border-radius: 999px; overflow: hidden; background: var(--untried); }}
.progress i {{ display: block; height: 100%; }}
.progress .e {{ background: var(--exact); }}
.progress .n {{ background: var(--near); }}
.progress .u {{ background: var(--untried); }}
.progress-labels {{ display: flex; justify-content: space-between; color: var(--muted); font-size: 11px; margin-top: 7px; }}
.band-svg {{ display: block; width: 100%; height: auto; overflow: visible; }}
.band-svg rect[data-status]:hover {{ filter: brightness(1.45); }}
.atlas {{ width: 100%; height: auto; display: block; border-radius: 6px; background: #0b1220; image-rendering: pixelated; }}
.grid2 {{ display: grid; grid-template-columns: 1fr 1fr; gap: 16px; }}
table {{ width: 100%; border-collapse: collapse; font-size: 12px; }}
th {{ color: var(--muted); font-size: 10px; letter-spacing: .7px; text-align: left; text-transform: uppercase; border-bottom: 1px solid var(--line); padding: 7px 6px; }}
td {{ border-bottom: 1px solid rgba(38,53,76,.55); padding: 7px 6px; white-space: nowrap; }}
td:first-child {{ color: #c9d7ea; }}
.exact-text {{ color: var(--exact); }}
.near-text {{ color: var(--near); }}
.note {{ color: var(--muted); font-size: 12px; margin: 10px 0 0; }}
footer {{ color: var(--muted); font-size: 12px; margin-top: 28px; display: flex; flex-wrap: wrap; gap: 8px 18px; justify-content: space-between; }}
@media (max-width: 760px) {{
  main {{ padding: 28px 16px 44px; }}
  .kpis {{ grid-template-columns: 1fr 1fr; }}
  .overview, .grid2 {{ grid-template-columns: 1fr; }}
  .overview {{ justify-items: center; }}
  .panel {{ padding: 17px; }}
  .kpi .value {{ font-size: 25px; }}
}}
</style>
</head>
<body>
<main>
  <header>
    <div class="eyebrow">Project Yamamura / coverage map</div>
    <h1>One executable.<br><span>{stats['done_pct']:.1f}% reconstructed.</span></h1>
    <p class="lede">A function-boundary view of the PowerPC code in <code>Block.elf</code>.
    Exact means byte-identical to the retail build; near means decompiled but not
    byte-identical; untouched means analysed by Ghidra but not yet reconstructed.</p>
    <div class="meta">Ghidra boundary inventory · {stats['ghidra_count']:,} analyzed functions ·
    {stats['known_not_ghidra']} recorded additions ·
    text range <code>0x{stats['text_start']:08X}–0x{stats['text_end']:08X}</code> ·
    generated {date.today().isoformat()}</div>
  </header>

  <section class="kpis" aria-label="Coverage summary">
    <div class="kpi exact"><div class="label">Exact</div><div class="value">{stats['exact']:,}</div><div class="sub">{exact_pct:.1f}% · {stats['verified_bytes']:,} verified bytes</div></div>
    <div class="kpi near"><div class="label">Near</div><div class="value">{stats['near']:,}</div><div class="sub">{near_pct:.1f}% · archived candidates</div></div>
    <div class="kpi todo"><div class="label">Untouched</div><div class="value">{stats['untried']:,}</div><div class="sub">{untried_pct:.1f}% · remaining boundaries</div></div>
    <div class="kpi"><div class="label">Total done</div><div class="value">{stats['done_pct']:.1f}%</div><div class="sub">{stats['done']:,} of {stats['total']:,} boundaries</div></div>
  </section>

  <section class="panel overview" aria-label="Overall coverage">
    <div>{donut_svg(stats)}</div>
    <div>
      <div class="panel-head"><div><h2>Overall coverage</h2><div class="panel-sub">Every analyzed function, including archived near misses</div></div></div>
      <div class="progress" role="progressbar" aria-valuemin="0" aria-valuemax="100" aria-valuenow="{stats['done_pct']:.1f}" aria-label="Reconstructed functions">
        <i class="e" style="width:{exact_pct:.4f}%"></i><i class="n" style="width:{near_pct:.4f}%"></i><i class="u" style="width:{untried_pct:.4f}%"></i>
      </div>
      <div class="progress-labels"><span>{stats['exact']:,} exact</span><span>{stats['near']:,} near</span><span>{stats['untried']:,} untouched</span></div>
      <div class="legend">
        <span><b class="swatch exact"></b> exact match</span>
        <span><b class="swatch near"></b> near miss</span>
        <span><b class="swatch untried"></b> untouched</span>
      </div>
      {note}
    </div>
  </section>

  <section class="panel" aria-label="Address coverage">
    <div class="panel-head"><div><h2>Address-space coverage</h2><div class="panel-sub">Stacked function counts across the {len(bands)} 64 KiB bands of <code>.text</code></div></div><div class="legend"><span><b class="swatch exact"></b>exact</span><span><b class="swatch near"></b>near</span><span><b class="swatch untried"></b>untouched</span></div></div>
    {band_svg(bands, stats)}
  </section>

  <section class="panel" aria-label="Function atlas">
    <div class="panel-head"><div><h2>Function atlas</h2><div class="panel-sub">Each tile is one Ghidra boundary, ordered by address; greener clusters are reconstructed</div></div></div>
    <canvas class="atlas" id="atlas" width="1280" height="560" role="img" aria-label="Tile grid of all analyzed functions, colored by status"></canvas>
    <div class="legend"><span><b class="swatch exact"></b>exact</span><span><b class="swatch near"></b>near</span><span><b class="swatch untried"></b>untouched</span><span>{stats['total']:,} tiles</span></div>
  </section>

  <section class="grid2" aria-label="Band details">
    <div class="panel"><div class="panel-head"><div><h2>Largest untouched bands</h2><div class="panel-sub">Useful next work queue</div></div></div><table><thead><tr><th>Band</th><th>Total</th><th>Exact</th><th>Near</th><th>Untouched</th><th>Done</th></tr></thead><tbody>{top_untouched}</tbody></table></div>
    <div class="panel"><div class="panel-head"><div><h2>Most complete bands</h2><div class="panel-sub">Where the existing source concentrates</div></div></div><table><thead><tr><th>Band</th><th>Total</th><th>Exact</th><th>Near</th><th>Untouched</th><th>Done</th></tr></thead><tbody>{top_done}</tbody></table></div>
  </section>

  <footer>
    <span>Boundary inventory: <a href="../config/function_boundaries.tsv">function_boundaries.tsv</a> · <a href="../README.md">repository</a></span>
    <span>Ghidra 12.1.2 · exact/near statuses from the project tables</span>
  </footer>
</main>
<script>
const DATA = {json.dumps(data, separators=(',', ':'))};
(function drawAtlas() {{
  const canvas = document.getElementById('atlas');
  if (!canvas) return;
  const codes = DATA.atlas;
  const cols = 256;
  const cell = 5;
  const rows = Math.ceil(codes.length / cols);
  const dpr = Math.min(2, window.devicePixelRatio || 1);
  const cw = cols * cell;
  const ch = rows * cell;
  canvas.width = cw * dpr;
  canvas.height = ch * dpr;
  canvas.style.aspectRatio = cw + ' / ' + ch;
  const ctx = canvas.getContext('2d');
  ctx.scale(dpr, dpr);
  const colors = {{E:'{COLORS['exact']}', N:'{COLORS['near']}', U:'{COLORS['untried']}'}};
  for (let i = 0; i < codes.length; i++) {{
    ctx.fillStyle = colors[codes[i]] || colors.U;
    ctx.fillRect((i % cols) * cell, Math.floor(i / cols) * cell, cell - 1, cell - 1);
  }}
}})();
</script>
</body>
</html>
"""


def render_svg(rows: list[Boundary], bands: list[Band],
               stats: dict[str, object]) -> str:
    width, height = 1200, 640
    bar_left, bar_top, bar_width, bar_height = 70, 268, 1060, 230
    bottom = bar_top + bar_height
    max_total = max(1, int(stats["max_band"]))
    step = bar_width / max(1, len(bands))
    bar_w = max(1.0, step - 1.0)
    bars = []
    for index, band in enumerate(bands):
        x = bar_left + index * step + (step - bar_w) / 2
        y = bottom
        for key in ("exact", "near", "untried"):
            count = getattr(band, key)
            if count:
                segment = bar_height * count / max_total
                y -= segment
                bars.append(
                    f'<rect x="{x:.2f}" y="{y:.2f}" width="{bar_w:.2f}" '
                    f'height="{segment:.2f}" fill="{COLORS[key]}"/>'
                )
    labels = "".join(
        f'<text x="{bar_left + index * step + step / 2:.2f}" y="{bottom + 18}" '
        f'text-anchor="middle" font-size="10" fill="{MUTED}">0x{bands[index].start:08X}</text>'
        for index in (0, len(bands) // 2, len(bands) - 1)
    ) if bands else ""
    grid = "".join(
        f'<line x1="{bar_left}" y1="{bottom - bar_height * tick:.2f}" '
        f'x2="{bar_left + bar_width}" y2="{bottom - bar_height * tick:.2f}" '
        f'stroke="{GRID}" stroke-width="1"/>'
        f'<text x="{bar_left - 12}" y="{bottom - bar_height * tick + 4:.2f}" '
        f'text-anchor="end" font-size="11" fill="{MUTED}">{int(round(max_total * tick))}</text>'
        for tick in (0, 0.5, 1.0)
    )
    exact_pct = stats["exact_pct"]
    near_pct = stats["near_pct"]
    bars_svg = "".join(bars)
    return f"""<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}" role="img" aria-label="Project Yamamura decompilation coverage">
<title>Project Yamamura decompilation coverage</title>
<rect width="{width}" height="{height}" rx="22" fill="{BG}"/>
<text x="48" y="48" fill="{COLORS['exact']}" font-family="Inter,Arial,sans-serif" font-size="12" font-weight="700" letter-spacing="2">PROJECT YAMAMURA / COVERAGE MAP</text>
<text x="48" y="98" fill="{TEXT}" font-family="Inter,Arial,sans-serif" font-size="36" font-weight="700">One executable. <tspan fill="{COLORS['exact']}">{stats['done_pct']:.1f}% reconstructed.</tspan></text>
<text x="48" y="126" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="14">Ghidra boundaries in Block.elf · exact means byte-identical · near means decompiled but not byte-identical</text>
<text x="48" y="174" fill="{COLORS['exact']}" font-family="Inter,Arial,sans-serif" font-size="29" font-weight="700">{stats['exact']:,}</text>
<text x="48" y="194" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11" letter-spacing="1">EXACT</text>
<text x="285" y="174" fill="{COLORS['near']}" font-family="Inter,Arial,sans-serif" font-size="29" font-weight="700">{stats['near']:,}</text>
<text x="285" y="194" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11" letter-spacing="1">NEAR</text>
<text x="522" y="174" fill="#a8b8cf" font-family="Inter,Arial,sans-serif" font-size="29" font-weight="700">{stats['untried']:,}</text>
<text x="522" y="194" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11" letter-spacing="1">UNTOUCHED</text>
<text x="760" y="174" fill="{TEXT}" font-family="Inter,Arial,sans-serif" font-size="29" font-weight="700">{stats['done_pct']:.1f}%</text>
<text x="760" y="194" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11" letter-spacing="1">DONE · {stats['done']:,} / {stats['total']:,}</text>
<rect x="48" y="212" width="1104" height="14" rx="7" fill="{COLORS['untried']}"/>
<rect x="48" y="212" width="{1104 * exact_pct / 100:.2f}" height="14" rx="7" fill="{COLORS['exact']}"/>
<rect x="{48 + 1104 * exact_pct / 100:.2f}" y="212" width="{1104 * near_pct / 100:.2f}" height="14" fill="{COLORS['near']}"/>
<text x="48" y="248" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="12">Address-space coverage · {len(bands)} bands of 64 KiB</text>
{grid}
{bars_svg}
{labels}
<text x="48" y="554" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="12">Ghidra 12.1.2 · {stats['ghidra_count']:,} analyzed + {stats['known_not_ghidra']} recorded boundaries · inventory: config/function_boundaries.tsv</text>
<text x="48" y="578" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="12">Text range 0x{stats['text_start']:08X}–0x{stats['text_end']:08X} · Stack analyzer disabled; analysis completed cleanly · generated {date.today().isoformat()}</text>
<circle cx="730" cy="244" r="4" fill="{COLORS['exact']}"/><text x="741" y="248" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11">exact</text>
<circle cx="793" cy="244" r="4" fill="{COLORS['near']}"/><text x="804" y="248" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11">near</text>
<circle cx="847" cy="244" r="4" fill="{COLORS['untried']}"/><text x="858" y="248" fill="{MUTED}" font-family="Inter,Arial,sans-serif" font-size="11">untouched</text>
</svg>
"""


def write_inventory(path: Path, rows: list[Boundary]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(
            "# Ghidra function-boundary inventory\n"
            "# Source: Ghidra 12.1.2 headless auto-analysis; Stack disabled, analysis completed cleanly.\n"
            "# entry\tend (exclusive)\tbytes\tstatus\tband\tname\tsource\t"
            "boundary\tverified_end\tmissing_source\tbody_bytes\tranges\t"
            "ghidra_name\tthunk\tnote\n"
        )
        for row in rows:
            fields = [
                f"{row.start:08X}",
                f"{row.end:08X}",
                str(row.end - row.start),
                row.status,
                f"{row.start >> 16:04X}",
                row.name,
                row.source,
                row.boundary,
                "" if row.verified_end is None else f"{row.verified_end:08X}",
                str(row.missing_source),
                str(row.body_bytes),
                str(row.ranges),
                row.ghidra_name,
                str(row.thunk),
                row.note,
            ]
            handle.write("\t".join(fields).rstrip("\t") + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ghidra", default="build/ghidra/functions_clean3.tsv")
    parser.add_argument("--exact", default="src/functions.tsv")
    parser.add_argument("--near", default="src/near")
    parser.add_argument("--bl-targets", default="build/all_bl_targets.txt")
    parser.add_argument("--inventory", default="config/function_boundaries.tsv")
    parser.add_argument("--html", default="docs/progress.html")
    parser.add_argument("--svg", default="docs/progress.svg")
    args = parser.parse_args()

    ghidra = load_ghidra(ROOT / args.ghidra)
    exact = load_exact(ROOT / args.exact)
    near = load_near(ROOT / args.near)
    bl_targets = load_bl_targets(ROOT / args.bl_targets)
    if not ghidra:
        raise SystemExit("Ghidra export contains no .text functions")
    rows = build_inventory(ghidra, exact, near, bl_targets)
    bands = make_bands(rows)
    stats = make_stats(rows, bands)

    write_inventory(ROOT / args.inventory, rows)
    (ROOT / args.html).write_text(
        render_html(rows, bands, stats), encoding="utf-8", newline="\n")
    (ROOT / args.svg).write_text(
        render_svg(rows, bands, stats), encoding="utf-8", newline="\n")

    print(f"Ghidra functions: {len(ghidra):,}")
    print(f"Inventory rows:   {len(rows):,}")
    print(f"Exact / near / untouched: {stats['exact']:,} / "
          f"{stats['near']:,} / {stats['untried']:,}")
    print(f"Near missing sources:     {stats['missing_near']:,}")
    print(f"Verified bytes:           {stats['verified_bytes']:,}")
    print(f"Bands:                    {len(bands):,}")
    print(f"Wrote {args.inventory}, {args.html}, {args.svg}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
