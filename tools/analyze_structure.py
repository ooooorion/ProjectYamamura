#!/usr/bin/env python3
"""Derive naming and source-grouping evidence from the verified function table.

The names emitted here are role aliases, not recovered original symbols.  The
matcher still keys on the first column of src/functions.tsv, so no source or
table symbol is renamed.  Outputs are proposal metadata only.

The optional `asm/import_calls.tsv` index adds named SDK import evidence
where a call site falls inside a matched range.  `asm/rodata.txt` is used only
for exact-start, code-like string references; raw dumps and game assets are not
copied into the generated files.

Usage:
    python tools/analyze_structure.py
"""

from __future__ import annotations

import collections
import hashlib
import re
from bisect import bisect_right
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TABLE = ROOT / "src" / "functions.tsv"
SYMBOLS = ROOT / "config" / "symbols.txt"
NAMES_OUT = ROOT / "config" / "function_names.tsv"
GROUPS_OUT = ROOT / "config" / "function_groups.tsv"
IMPORTS_OUT = ROOT / "config" / "function_imports.tsv"
STRINGS_OUT = ROOT / "config" / "function_strings.tsv"
ASM_IMPORT_CALLS = ROOT / "asm" / "import_calls.tsv"
ASM_RODATA = ROOT / "asm" / "rodata.txt"
NAMES_DOC = ROOT / "docs" / "FUNCTION_NAMES.md"
GROUPS_DOC = ROOT / "docs" / "FUNCTION_GROUPS.md"

DEFAULT_FLAGS = "-c -O2"

ROLE_CLASSES = {
    "address_getters": "direct loads from a fixed data address",
    "constant_returns": "functions whose whole body is a literal return",
    "field_getters": "read one object field",
    "field_setters": "store one argument into an object field",
    "field_predicates": "test one object field",
    "vector_appends": "bounded count/capacity/items append",
    "vtable_dispatch": "virtual-call dispatch",
    "wrappers": "forward or tail-call another function",
    "arg_arithmetic": "small argument arithmetic",
    "sdk_api_callers": "calls a named SDK import inside the matched range",
    "string_refs": "returns a code-related string literal",
}


def clean(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def compact(text: str) -> str:
    return " ".join(clean(text).split())


def body_of(source: str, name: str):
    pattern = re.compile(
        r"(?m)^[^\n;{}]*\b" + re.escape(name) + r"\s*\([^;{}]*\)\s*\{"
    )
    match = pattern.search(source)
    if not match:
        return None, None
    start = source.index("{", match.start())
    depth = 0
    for pos in range(start, len(source)):
        if source[pos] == "{":
            depth += 1
        elif source[pos] == "}":
            depth -= 1
            if depth == 0:
                return source[start + 1 : pos], match.group(0)
    return None, None


def parse_table():
    rows = []
    for line in TABLE.read_text(encoding="utf-8").splitlines():
        if not line or line.startswith("#"):
            continue
        parts = line.split("\t")
        rows.append(
            {
                "symbol": parts[0],
                "start": parts[1],
                "end": parts[2],
                "source": parts[3],
                "cflags": parts[4] if len(parts) > 4 and parts[4] else DEFAULT_FLAGS,
            }
        )
    return rows


def read_symbols():
    names = set()
    for line in SYMBOLS.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0]
        if "=" in line:
            names.add(line.split("=", 1)[0].strip())
    return names


def slug(text: str) -> str:
    text = re.sub(r"[^A-Za-z0-9]+", "_", text).strip("_").lower()
    return text or "unnamed"


def data_refs(body: str):
    return sorted(set(re.findall(r"\b0x(1[0-9A-Fa-f]{7})\b", body)))


def internal_calls(body: str, known: set[str]):
    return sorted(
        {
            name
            for name in re.findall(r"\b([A-Za-z_]\w*)\s*\(", body)
            if name in known and name not in {"if", "while", "switch", "sizeof"}
        }
    )


def role_for(body: str, known: set[str]):
    """Return (role stem, class, confidence, evidence) or None."""
    s = compact(body)
    m = re.fullmatch(r"return \*\(([^)]+)\)(0x[0-9A-Fa-f]+);", s)
    if m:
        typ = m.group(1).replace(" ", "").replace("*", "")
        return (
            f"get_{typ}_{m.group(2)[2:].upper()}",
            "address_getters",
            "strong",
            f"returns *{typ} at {m.group(2)}",
        )
    m = re.fullmatch(r"return (0x[0-9A-Fa-f]+|\d+);", s)
    if m:
        literal = m.group(1)
        return (
            f"const_{literal}",
            "constant_returns",
            "strong",
            f"returns literal {literal}",
        )
    m = re.fullmatch(r"return (?:value|arg\d+)\s*\+\s*(\d+);", s)
    if m:
        return (
            f"arg0_plus_{m.group(1)}",
            "arg_arithmetic",
            "strong",
            f"returns first argument plus {m.group(1)}",
        )
    m = re.fullmatch(r"return (?:value|arg\d+)\s*-\s*(\d+);", s)
    if m:
        return (
            f"arg0_minus_{m.group(1)}",
            "arg_arithmetic",
            "strong",
            f"returns first argument minus {m.group(1)}",
        )
    if "self->count >= self->capacity" in s and "self->items[self->count] = value" in s:
        return (
            "bounded_append",
            "vector_appends",
            "medium",
            "bounds check against count/capacity then stores through items",
        )
    m = re.fullmatch(
        r"if \(arg1 == self->([A-Za-z_]\w*)\) \{? return 0; \}? "
        r"self->vtable\[(\d+)\]\(\); return 1;",
        s,
    )
    if m:
        return (
            f"dispatch_vtable_{m.group(2)}",
            "vtable_dispatch",
            "medium",
            f"compares {m.group(1)} then calls virtual slot {m.group(2)}",
        )
    m = re.fullmatch(r"return self->([A-Za-z_]\w*);", s)
    if m:
        return (f"get_{m.group(1)}", "field_getters", "medium", f"loads {m.group(1)}")
    m = re.fullmatch(r"self->([A-Za-z_]\w*) = (?:value|arg\d+);", s)
    if m:
        return (
            f"set_{m.group(1)}",
            "field_setters",
            "medium",
            f"stores the value argument in {m.group(1)}",
        )
    m = re.fullmatch(r"return self->([A-Za-z_]\w*) == (0x[0-9A-Fa-f]+|\d+);", s)
    if m:
        return (
            f"is_{m.group(1)}_eq_{m.group(2)}",
            "field_predicates",
            "medium",
            f"compares {m.group(1)} with {m.group(2)}",
        )
    m = re.fullmatch(r"return self->([A-Za-z_]\w*) != 0;", s)
    if m:
        return (
            f"has_{m.group(1)}",
            "field_predicates",
            "medium",
            f"tests {m.group(1)} for nonzero",
        )
    m = re.fullmatch(r"return self->([A-Za-z_]\w*) == 0;", s)
    if m:
        return (
            f"lacks_{m.group(1)}",
            "field_predicates",
            "medium",
            f"tests {m.group(1)} for zero",
        )
    m = re.fullmatch(r"return ([A-Za-z_]\w*)\(.*\);", s)
    if m and m.group(1) in known:
        return (
            f"forward_to_{m.group(1)}",
            "wrappers",
            "medium",
            f"returns the result of {m.group(1)}",
        )
    m = re.fullmatch(r"(?:return )?([A-Za-z_]\w*)\(.*\);", s)
    if m and m.group(1) in known:
        return (
            f"wrapper_{m.group(1)}",
            "wrappers",
            "medium",
            f"single call to {m.group(1)}",
        )
    return None


def load_asm_imports(rows):
    """Map import call sites into matched ranges, when the asm index exists."""
    empty = {
        "available": False,
        "functions": {},
        "sites": 0,
        "imports": 0,
        "matched_sites": 0,
        "outside_sites": 0,
    }
    if not ASM_IMPORT_CALLS.is_file():
        return empty

    ordered = sorted(rows, key=lambda row: row["start"])
    starts = [int(row["start"], 16) for row in ordered]
    calls = collections.defaultdict(list)
    all_imports = set()
    sites = 0
    outside = 0
    for line in ASM_IMPORT_CALLS.read_text(encoding="utf-8").splitlines()[1:]:
        parts = line.split("\t")
        if len(parts) != 5:
            continue
        caller, kind, module, name, _stub = parts
        address = int(caller, 16)
        sites += 1
        all_imports.add((module, name))
        index = bisect_right(starts, address) - 1
        if index < 0 or address > int(ordered[index]["end"], 16):
            outside += 1
            continue
        calls[ordered[index]["symbol"]].append((module, name, kind))

    functions = {}
    for symbol, entries in calls.items():
        unique = sorted({(module, name) for module, name, _kind in entries})
        modules = sorted({module for module, _name in unique})
        functions[symbol] = {
            "modules": modules,
            "imports": unique,
            "sites": len(entries),
        }
    return {
        "available": True,
        "functions": functions,
        "sites": sites,
        "imports": len(all_imports),
        "matched_sites": sum(entry["sites"] for entry in functions.values()),
        "outside_sites": outside,
    }


def import_role(entry):
    """Return a conservative API-caller alias for one matched function."""
    if not entry or not entry["imports"]:
        return None
    unique = entry["imports"]
    modules = entry["modules"]
    if len(unique) == 1:
        module, name = unique[0]
        stem = "calls_" + slug(f"{module}_{name}")[:56]
        evidence = f"calls {module}.{name} at {entry['sites']} matched site(s)"
    else:
        stem = "calls_" + slug("_and_".join(modules)) + f"_{len(unique)}_apis"
        names = "; ".join(f"{module}.{name}" for module, name in unique)
        evidence = f"calls {len(unique)} SDK imports: {names}"
    return (stem, "sdk_api_callers", "strong", evidence)


def is_code_string(text):
    """Reject short printable bytes that are really floats or table data."""
    if len(text) < 8:
        return False
    if any(separator in text for separator in "\\/%_"):
        return True
    if text.endswith((".c", ".h", ".cpp", ".hpp", ".szs", ".bfres", ".pack", ".xml", ".txt")):
        return True
    return bool(re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]{7,}", text))


def load_asm_strings(rows, bodies):
    """Find exact-start code strings referenced by matched source ranges."""
    empty = {
        "available": False,
        "functions": {},
        "strings": 0,
        "refs": 0,
    }
    if not ASM_RODATA.is_file():
        return empty

    memory = {}
    for line in ASM_RODATA.read_text(encoding="ascii", errors="replace").splitlines():
        parts = line.split()
        if len(parts) < 5 or not re.fullmatch(r"[0-9a-fA-F]{8}", parts[0]):
            continue
        address = int(parts[0], 16)
        try:
            words = [int(word, 16) for word in parts[1:5]]
        except ValueError:
            continue
        for index, word in enumerate(words):
            for byte_index in range(4):
                memory[address + index * 4 + byte_index] = (
                    word >> (24 - byte_index * 8)
                ) & 0xFF

    strings = {}
    for address in sorted(memory):
        if not 32 <= memory[address] < 127:
            continue
        if address - 1 in memory and 32 <= memory[address - 1] < 127:
            continue
        end = address
        while end in memory and 32 <= memory[end] < 127:
            end += 1
        if memory.get(end) != 0:
            continue
        text = "".join(chr(memory[position]) for position in range(address, end))
        if is_code_string(text):
            strings[address] = text

    functions = {}
    refs = 0
    for row in rows:
        for address_text in data_refs(bodies[row["symbol"]]):
            address = int(address_text, 16)
            if not 0x10000000 <= address < 0x10181040:
                continue
            refs += 1
            if address in strings:
                functions.setdefault(row["symbol"], []).append((address, strings[address]))
    return {
        "available": True,
        "functions": functions,
        "strings": len(strings),
        "refs": refs,
    }


def string_role(entries):
    if not entries:
        return None
    address, text = entries[0]
    if "\\" in text or "/" in text:
        stem = "returns_path_" + slug(text)[:56]
    else:
        stem = "returns_string_" + slug(text)[:56]
    return (
        stem,
        "string_refs",
        "strong",
        f"returns pointer to code string at 0x{address:08X}: {text}",
    )


def make_names(rows, bodies, known, asm, strings):
    symbols = read_symbols()
    named = {}
    for row in rows:
        name = row["symbol"]
        if not name.startswith("func_"):
            named[name] = (
                name,
                "named",
                "strong" if name in symbols else "medium",
                "existing name in config/symbols.txt and byte-matched table",
            )
            continue
        role = role_for(bodies[name], known)
        specific = string_role(strings["functions"].get(name))
        if specific:
            role = specific
        elif role is None and asm["available"]:
            role = import_role(asm["functions"].get(name))
        if role:
            named[name] = role

    counts = collections.Counter(role[0] for role in named.values())
    rows_out = []
    for row in rows:
        name = row["symbol"]
        if name not in named:
            continue
        stem, role_class, confidence, evidence = named[name]
        display = stem
        if counts[stem] > 1:
            display = f"{stem}__{row['start']}"
        rows_out.append(
            {
                "symbol": name,
                "start": row["start"],
                "end": row["end"],
                "suggested_name": display,
                "role_stem": stem,
                "class": role_class,
                "confidence": confidence,
                "evidence": evidence,
            }
        )
    return rows_out, named


def build_call_components(rows, bodies, known):
    by_start = {row["symbol"]: row["start"] for row in rows}
    edges = collections.defaultdict(set)
    shared = collections.Counter()
    call_pairs = 0
    data_users = collections.defaultdict(list)
    for symbol, body in bodies.items():
        for callee in internal_calls(body, known):
            if callee in bodies and callee != symbol:
                if by_start[symbol][:4] == by_start[callee][:4]:
                    edges[symbol].add(callee)
                    edges[callee].add(symbol)
                    call_pairs += 1
        for address in data_refs(body):
            data_users[address].append(symbol)
    for address, users in data_users.items():
        if len(users) < 2:
            continue
        shared[address] = len(users)
        for user in users:
            for other in users:
                if user != other and by_start[user][:4] == by_start[other][:4]:
                    edges[user].add(other)

    parent = {symbol: symbol for symbol in bodies}

    def find(item):
        while parent[item] != item:
            parent[item] = parent[parent[item]]
            item = parent[item]
        return item

    def union(a, b):
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[rb] = ra

    for symbol, neighbours in edges.items():
        for other in neighbours:
            union(symbol, other)
    components = collections.defaultdict(list)
    for symbol in bodies:
        components[find(symbol)].append(symbol)
    result = []
    for members in components.values():
        if len(members) < 3:
            continue
        members = sorted(members)
        starts = [by_start[m] for m in members]
        data_cells = {
            address
            for member in members
            for address in data_refs(bodies[member])
            if shared.get(address, 0) > 1
        }
        result.append(
            {
                "members": members,
                "start": min(starts),
                "end": max(by_start[m] for m in members),
                "data": sorted(data_cells),
            }
        )
    result.sort(key=lambda item: (-len(item["members"]), item["start"]))
    return result


def group_row(group_id, kind, path, members, sizes, flags, evidence):
    flags = sorted({f for f in flags})
    cflags = flags[0] if len(flags) == 1 else "MIXED"
    return {
        "group_id": group_id,
        "kind": kind,
        "path": path,
        "count": len(members),
        "bytes": sum(sizes[m] for m in members),
        "cflags": cflags,
        "members": members,
        "evidence": evidence,
    }


def build_groups(rows, bodies, named, known):
    sizes = {
        row["symbol"]: int(row["end"], 16) - int(row["start"], 16) + 4 for row in rows
    }
    row_by_symbol = {row["symbol"]: row for row in rows}
    groups = []

    # Cross-cutting role groups are the low-risk pilots.
    classes = collections.defaultdict(list)
    for symbol, role in named.items():
        if role[1] not in {"named", "sdk_api_callers", "string_refs"}:
            classes[role[1]].append(symbol)
    for role_class in sorted(classes):
        members = sorted(classes[role_class], key=lambda m: row_by_symbol[m]["start"])
        if len(members) < 2:
            continue
        groups.append(
            group_row(
                f"R{len(groups)+1:02d}",
                "role",
                f"src/readable/roles/{role_class}.c",
                members,
                sizes,
                [row_by_symbol[m]["cflags"] for m in members],
                f"{ROLE_CLASSES[role_class]}; {len({named[m][0] for m in members})} role stems",
            )
        )

    # Exact normalized-body clones are safe mechanical candidates.
    clones = collections.defaultdict(list)
    for symbol, body in bodies.items():
        clones[hashlib.sha256(compact(body).encode()).hexdigest()].append(symbol)
    clone_groups = []
    for members in clones.values():
        if len(members) < 2:
            continue
        members = sorted(members, key=lambda m: row_by_symbol[m]["start"])
        stems = {named[m][0] for m in members if m in named}
        semantic = len(stems) == 1
        if not semantic and len(members) < 3:
            continue
        clone_groups.append((members, stems))
    clone_groups.sort(key=lambda item: (-len(item[0]), item[0][0]))
    used_paths = {group["path"] for group in groups}
    for members, stems in clone_groups:
        stem = next(iter(stems)) if len(stems) == 1 else "clone_" + hashlib.sha1(
            compact(bodies[members[0]]).encode()
        ).hexdigest()[:8]
        group_id = f"C{len(groups)+1:02d}"
        path = f"src/readable/clones/{slug(stem)}.c"
        if path in used_paths:
            path = f"src/readable/clones/{slug(stem)}_{group_id.lower()}.c"
        used_paths.add(path)
        groups.append(
            group_row(
                group_id,
                "clone",
                path,
                members,
                sizes,
                [row_by_symbol[m]["cflags"] for m in members],
                "identical normalized body: " + compact(bodies[members[0]])[:96],
            )
        )

    # Same-band call/data components approximate plausible original units.
    components = build_call_components(rows, bodies, known)
    for component in components[:24]:
        groups.append(
            group_row(
                f"G{len(groups)+1:02d}",
                "region",
                f"src/readable/regions/region_{component['start']}_{component['end']}.c",
                component["members"],
                sizes,
                [row_by_symbol[m]["cflags"] for m in component["members"]],
                f"internal call/data component within one 64 KB band; "
                f"{len(component['data'])} shared data cells",
            )
        )
    return groups, components


def write_tsv(path, fields, rows):
    lines = ["\t".join(fields)]
    for row in rows:
        lines.append("\t".join(str(row[field]) for field in fields))
    path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def md_escape(text):
    return str(text).replace("|", "\\|")


def write_imports(asm):
    if not asm["available"]:
        return
    rows = []
    for symbol, entry in asm["functions"].items():
        row = next(row for row in parse_table() if row["symbol"] == symbol)
        rows.append(
            {
                "symbol": symbol,
                "start": row["start"],
                "end": row["end"],
                "sites": entry["sites"],
                "imports": "; ".join(f"{m}.{n}" for m, n in entry["imports"]),
                "modules": "; ".join(entry["modules"]),
            }
        )
    rows.sort(key=lambda row: row["start"])
    write_tsv(
        IMPORTS_OUT,
        ["symbol", "start", "end", "sites", "imports", "modules"],
        rows,
    )


def write_strings(strings):
    if not strings["available"]:
        return
    rows = []
    for symbol, entries in strings["functions"].items():
        source_row = next(row for row in parse_table() if row["symbol"] == symbol)
        for address, text in entries:
            rows.append(
                {
                    "symbol": symbol,
                    "start": source_row["start"],
                    "end": source_row["end"],
                    "address": f"{address:08X}",
                    "string": text.replace("\t", "\\t").replace("\n", "\\n"),
                }
            )
    rows.sort(key=lambda row: (row["start"], row["address"]))
    write_tsv(
        STRINGS_OUT,
        ["symbol", "start", "end", "address", "string"],
        rows,
    )


def write_names_doc(rows, names, asm, strings):
    by_stem = collections.defaultdict(list)
    for item in names:
        by_stem[(item["role_stem"], item["class"], item["confidence"], item["evidence"])].append(
            item["symbol"]
        )
    ranked = sorted(by_stem.items(), key=lambda item: (-len(item[1]), item[0][0]))
    conf = collections.Counter(item["confidence"] for item in names)
    classes = collections.Counter(item["class"] for item in names)
    lines = [
        "# Function-name evidence catalog",
        "",
        "Generated by `python tools/analyze_structure.py`. This is a role-name",
        "catalog, **not** a claim that the original source used these names.",
        "The verified symbols remain `func_XXXXXXXX`; the matcher still keys on",
        "`src/functions.tsv`.",
        "",
        "## Coverage",
        "",
        "| Measure | Value |",
        "|---|---:|",
        f"| Matched functions parsed | {len(rows)} |",
        f"| Functions with a role alias | {len(names)} |",
        f"| Distinct role stems | {len(by_stem)} |",
        f"| Strong / medium confidence | {conf['strong']} / {conf['medium']} |",
        "",
    ]
    aliases = {item["symbol"]: item["suggested_name"] for item in names}
    if asm["available"]:
        lines += [
            "## SDK import evidence",
            "",
            f"`asm/import_calls.tsv` names {asm['imports']} SDK entry points across "
            f"{asm['sites']:,} call sites. Only {asm['matched_sites']} of those sites "
            f"({len(asm['functions'])} functions) fall inside the current matched "
            f"ranges; {asm['outside_sites']:,} belong to unmatched code. The overlap "
            "is therefore useful evidence, not broad coverage.",
            "",
            "A named call proves that the function reaches that SDK entry point. It",
            "does not by itself prove the surrounding operation, so these remain role",
            "aliases.",
            "",
            "| Function | SDK sites | Import(s) | Suggested alias |",
            "|---|---:|---|---|",
        ]
        for symbol, entry in sorted(
            asm["functions"].items(),
            key=lambda item: next(r["start"] for r in rows if r["symbol"] == item[0]),
        ):
            imports = "; ".join(f"`{m}.{n}`" for m, n in entry["imports"])
            lines.append(
                f"| `{symbol}` | {entry['sites']} | {imports} | "
                f"`{aliases.get(symbol, symbol)}` |"
            )
        lines += [
            "",
            "The full mapping is in `config/function_imports.tsv`. Raw `asm/`",
            "artefacts are not committed.",
            "",
        ]
    if strings["available"]:
        lines += [
            "## String evidence",
            "",
            f"{strings['refs']} absolute rodata references occur in matched source. "
            "Only strings that start exactly at the referenced address, contain a "
            "path or identifier shape, and are at least eight bytes long are accepted. "
            "This rejects four-byte float data that happens to be printable.",
            "",
            "| Function | Address | Code-related literal | Suggested alias |",
            "|---|---|---|---|",
        ]
        for symbol, entries in sorted(strings["functions"].items()):
            for address, text in entries:
                lines.append(
                    f"| `{symbol}` | `0x{address:08X}` | `{md_escape(text)}` | "
                    f"`{aliases.get(symbol, symbol)}` |"
                )
        lines += [
            "",
            "The accepted references are in `config/function_strings.tsv`.",
            "Game assets and unrelated game-facing text remain out of the repository.",
            "",
        ]
    lines += [
        "## Evidence rules",
        "",
        "- **Strong**: the entire body proves the role, for example a fixed-address",
        "  load or a literal return. A named import call also supports the narrow",
        "  role “calls this API”. This proves behavior, not the original name.",
        "- **Medium**: the body proves a field operation, wrapper, dispatch or",
        "  vector shape, but does not identify the object or subsystem.",
        "- **Named**: the function already has a name in `config/symbols.txt` and",
        "  is byte-matched. Keep the existing spelling.",
        "",
        "Names are made unique for display by appending `__<address>` when several",
        "functions share the same role stem. That suffix is not a recovered symbol.",
        "",
        "## Largest role families",
        "",
        "| Role stem | Count | Class | Confidence | Evidence |",
        "|---|---:|---|---|---|",
    ]
    for (stem, role_class, confidence, evidence), members in ranked[:30]:
        lines.append(
            f"| `{md_escape(stem)}` | {len(members)} | `{role_class}` | "
            f"{confidence} | {md_escape(evidence)} |"
        )
    lines += [
        "",
        "## Role-class distribution",
        "",
        "| Class | Functions |",
        "|---|---:|",
    ]
    for role_class, count in sorted(classes.items(), key=lambda item: (-item[1], item[0])):
        lines.append(f"| `{role_class}` | {count} |")
    lines += [
        "",
        "## Files",
        "",
        "- `config/function_names.tsv`: one row per alias candidate.",
        "- `config/function_imports.tsv`: matched functions with SDK import sites.",
        "- `config/function_strings.tsv`: accepted code-related string references.",
        "- `docs/FUNCTION_GROUPS.md`: source-grouping candidates.",
        "- `docs/HUMAN_READABLE.md`: how to apply names and types without",
        "  changing bytes.",
        "",
        "## What would strengthen a name",
        "",
        "1. A string or data-table reference that identifies the subsystem.",
        "2. A caller with a known name and a matching argument contract.",
        "3. A shared object model whose offsets and signedness agree across",
        "   every user.",
        "4. A second named import call that narrows the operation.",
        "",
        "Until one of those is available, prefer the role alias in a comment and",
        "keep the `func_` symbol in code.",
    ]
    NAMES_DOC.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def write_groups_doc(groups, components, rows):
    roles = [g for g in groups if g["kind"] == "role"]
    clones = [g for g in groups if g["kind"] == "clone"]
    regions = [g for g in groups if g["kind"] == "region"]
    covered = {m for g in groups for m in g["members"]}
    lines = [
        "# Source-grouping candidates",
        "",
        "Generated by `python tools/analyze_structure.py`. Nothing has been moved",
        "or renamed. These are candidate translation units for a verified",
        "reorganization.",
        "",
        "## Candidate tiers",
        "",
        "| Tier | Groups | Functions | Use |",
        "|---|---:|---:|---|",
        f"| Role groups | {len(roles)} | {sum(g['count'] for g in roles)} | low-risk pilot; same behavior class |",
        f"| Exact-body clones | {len(clones)} | {sum(g['count'] for g in clones)} | mechanical deduplication |",
        f"| Regional call/data clusters | {len(regions)} | {sum(g['count'] for g in regions)} | closest local approximation to original units |",
        f"| Unique functions in any proposal | — | {len(covered)} | overlap exists between tiers |",
        "",
        "Role groups are cross-cutting: they make the source easier to read but",
        "are not evidence that the original had one `constants.c`. Regional",
        "clusters use internal calls and shared data addresses inside one 64 KB",
        "band; they are the better hypothesis for original file boundaries.",
        "",
        "## Low-risk role groups",
        "",
        "| Group | Proposed file | Functions | Bytes | Flags | Evidence |",
        "|---|---|---:|---:|---|---|",
    ]
    for group in roles:
        lines.append(
            f"| `{group['group_id']}` | `{group['path']}` | {group['count']} | "
            f"{group['bytes']} | `{group['cflags']}` | {md_escape(group['evidence'])} |"
        )
    lines += [
        "",
        "## Exact-body clone groups (largest)",
        "",
        "| Group | Proposed file | Functions | Bytes | Flags |",
        "|---|---|---:|---:|---|",
    ]
    for group in sorted(clones, key=lambda g: (-g["count"], g["group_id"]))[:20]:
        lines.append(
            f"| `{group['group_id']}` | `{group['path']}` | {group['count']} | "
            f"{group['bytes']} | `{group['cflags']}` |"
        )
    lines += [
        "",
        "## Regional call/data clusters (largest)",
        "",
        "| Group | Proposed file | Functions | Bytes | Flags | Shared data cells |",
        "|---|---|---:|---:|---|---:|",
    ]
    by_id = {g["group_id"]: g for g in groups}
    for component in components[:16]:
        group = next(
            g
            for g in regions
            if set(g["members"]) == set(component["members"])
        )
        lines.append(
            f"| `{group['group_id']}` | `{group['path']}` | {group['count']} | "
            f"{group['bytes']} | `{group['cflags']}` | {len(component['data'])} |"
        )
    lines += [
        "",
        "## Proposed layout",
        "",
        "```",
        "src/readable/",
        "  roles/          cross-cutting behavior families (pilot)",
        "  clones/         identical normalized bodies",
        "  regions/        same-band call/data components (layout hypothesis)",
        "```",
        "",
        "Keep `src/functions.tsv` as the verification table. A move is complete",
        "only when the table points at the new file and every affected row still",
        "matches. Do not put rows with different compiler flags in one unit.",
        "",
        "## Suggested pilot order",
        "",
        "1. **Address getters** — direct loads, no calls, strongest behavior labels.",
        "2. **Constant returns** — identical bodies; mechanically easy to verify.",
        "3. **Bounded appends** — three related functions with an explicit",
        "   count/capacity/items model.",
        "4. **Regional clusters** — only after the mechanical pilots pass, because",
        "   a larger translation unit can change inlining and literal placement.",
        "",
        "## Verification",
        "",
        "```sh",
        "python tools/match.py > build/match_before.log",
        "# move one group and update the table paths",
        "python tools/match.py > build/match_after.log",
        "```",
        "",
        "Both runs must exit 0 and report the same row count. Treat any size or",
        "`DIFF` change as a failed move, even when the source looks equivalent.",
        "",
        "## Files",
        "",
        "- `config/function_groups.tsv`: full machine-readable group list.",
        "- `config/function_names.tsv`: role aliases for group members.",
        "- `docs/HUMAN_READABLE.md`: transformation rules and worked examples.",
    ]
    GROUPS_DOC.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def main():
    rows = parse_table()
    known = {row["symbol"] for row in rows} | read_symbols()
    known |= {"memcpy", "memset", "strlen", "strcmp", "exit"}
    bodies = {}
    failed = []
    for row in rows:
        body, _ = body_of((ROOT / row["source"]).read_text(encoding="utf-8"), row["symbol"])
        if body is None:
            failed.append(row["symbol"])
        else:
            bodies[row["symbol"]] = body
    if failed:
        raise SystemExit(f"could not parse bodies: {failed[:10]}")

    asm = load_asm_imports(rows)
    strings = load_asm_strings(rows, bodies)
    names, named = make_names(rows, bodies, known, asm, strings)
    groups, components = build_groups(rows, bodies, named, known)
    write_tsv(
        NAMES_OUT,
        ["symbol", "start", "end", "suggested_name", "role_stem", "class", "confidence", "evidence"],
        names,
    )
    write_imports(asm)
    write_strings(strings)
    write_tsv(
        GROUPS_OUT,
        ["group_id", "kind", "path", "count", "bytes", "cflags", "members", "evidence"],
        [
            {**group, "members": ",".join(group["members"])}
            for group in groups
        ],
    )
    write_names_doc(rows, names, asm, strings)
    write_groups_doc(groups, components, rows)
    print(
        f"parsed={len(rows)} aliases={len(names)} groups={len(groups)} "
        f"role={sum(g['kind']=='role' for g in groups)} "
        f"clone={sum(g['kind']=='clone' for g in groups)} "
        f"region={sum(g['kind']=='region' for g in groups)} "
        f"import_functions={len(asm['functions'])} import_sites={asm['matched_sites']} "
        f"string_functions={len(strings['functions'])} rodata_refs={strings['refs']}"
    )


if __name__ == "__main__":
    main()
