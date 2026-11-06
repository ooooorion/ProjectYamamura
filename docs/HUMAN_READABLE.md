# Making matched functions readable without losing byte accuracy

The current source is deliberately machine-shaped: one function per file, local
`typedef struct { ... }` blocks, `pad` arrays, `func_XXXXXXXX` symbols, and
sometimes the whole m2c compatibility macro header. That shape is cheap to
compile, diff and revert. Readability is a second pass, not a replacement for
the verification scaffold.

This guide applies to the 1,667 byte-matched rows in `src/functions.tsv`. The
generated [name catalog](FUNCTION_NAMES.md) and [grouping candidates](FUNCTION_GROUPS.md)
are evidence inventories; they do not rename or move anything.

## Invariants to preserve

1. **The table symbol is the lookup key.** `tools/match.py` compiles the source
   named in column four and looks up the symbol named in column one. Do not
   rename that symbol until an alias mechanism exists. Put the readable name in
   `config/function_names.tsv`, a comment, or a prototype comment.
2. **Keep the row's compiler flags.** The startup rows use `-Ospace`; default
   rows use `-O2`. Mixing them in one translation unit invalidates the result.
3. **Preserve field width and signedness.** `s32` versus `u32` changes `cmpw`
   versus `cmplw`; `s16` versus `s32` changes load/store width and every later
   offset. Add a pad; do not tighten a struct to make it look natural.
4. **Preserve statement order and temporaries.** A separate `count = count + 1`
   after `items[count] = value` can be what stops the compiler from proving
   non-aliasing. Do not "simplify" it to `count++` without re-matching.
5. **Preserve linkage.** Do not add `static`, change a return type, or reorder
   parameters unless the target code and relocation evidence require it.
6. **Do not invent a data symbol.** Replacing `0x1018953C` with a name is safe
   only when the name resolves to the same address and the relocation encodes
   the same bits. The matcher must not report `BLOCKED`.
7. **A group is not a merge.** Combining translation units can change inlining,
   literal-pool placement and branch relocation layout. Verify the grouped
   unit, not only each function in isolation.

## Step 1: attach evidence before changing source

Use three confidence levels:

| Level | Evidence | What it can justify |
|---|---|---|
| Strong | Named import/string, known caller contract, or whole-body behavior | A role name in metadata or a comment |
| Medium | Shared object model, repeated field/constant pattern, internal call cluster | A descriptive field or family name |
| Weak | Similar shape only | A `family` note, not a name |

The generated catalog uses names such as `get_f32_100C92A8` and
`is_field_360_eq_0`. Those describe behavior; they are not claims about the
original source symbol. Keep the `func_` symbol in code and use the role name
in comments until there is stronger evidence.

When an import index is available, prefer evidence in this order:

1. a named import called by the function;
2. a string or data-table reference at a known address;
3. a named caller and a matching argument contract;
4. a shared struct whose offsets and signedness agree across all users.

If none of those exists, do not promote a guess into a C identifier.

## Step 2: normalize types and object models

### Local type first

Start with the type already in the function file. Replace `M2C_UNK` and raw
casts one at a time, recompiling after each change. A readable signature is:

```c
/* 0x02686968, 12 bytes. Role: get_f32_100C92A8 (strong). */
f32 func_02686968(void) {
    return *(f32 *)0x100C92A8;
}
```

The comment records the role; the code still uses the verifiable symbol.

### Promote a shared model only when the evidence agrees

A shared struct is justified when at least three functions use the same offset,
width and signedness. Keep all gaps explicit:

```c
/* offsets proved by cmpw/load/store widths in the listed functions */
typedef struct {
    s32 count;      /* +0x00 */
    s32 capacity;   /* +0x04 */
    u32 *items;     /* +0x08 */
} Vec;
```

Rules:

- build the struct from the union of accesses, not from a screenshot of one
  function;
- keep `pad` arrays rather than packed fields;
- no bitfields and no `__attribute__((packed))`;
- name a field `field_XXX` until its role is proved;
- record the evidence in a comment next to the declaration, not only in a
  commit message.

`func_02020410`, `func_02031278` and `func_020312A4` are the current
bounded-append family. `func_020359B4` has a similar triple at
`+0x44/+0x48/+0x4C` but also a different array at `+0xD0`; it is not the same
object. Do not merge the models just because the words "count", "capacity" and
"items" appear in both.

## Step 3: make the body readable without changing codegen

Prefer changes that cannot affect the emitted instructions:

- delete the unused m2c compatibility macro block after confirming the file
  still compiles;
- replace `M2C_UNK` with the narrowest type that reproduces the instructions;
- give locals and parameters role names;
- add offset and instruction comments;
- keep explicit casts when they carry signedness or width information;
- keep the original include set until the file is known not to need it.

Be suspicious of changes that can affect optimization:

- folding a temporary into one expression;
- replacing a separate increment with `++`;
- changing `if` structure or early returns;
- reordering independent stores;
- making a helper `static` or `inline`;
- moving a function into a larger translation unit.

Those are allowed, but they require a new byte match. The goal is not shorter
source; it is source a person can explain while the object stays identical.

## Step 4: choose a layout deliberately

There are two different questions:

1. **Can these functions share a file mechanically?** See the role and clone
   groups in `config/function_groups.tsv`.
2. **Did the original program put them in one file?** The regional clusters
   are a weaker hypothesis based on internal calls and shared data addresses
   inside one 64 KB band. They are not proof.

Use this order:

1. address getters and constant returns (no calls, strongest role labels);
2. exact-body clones with identical flags;
3. bounded appends behind a shared model;
4. regional call/data clusters only after the mechanical pilots pass.

Proposed layout (not applied):

```text
src/readable/
  roles/       cross-cutting behavior families
  clones/      identical normalized bodies
  regions/     same-band call/data components
```

Keep functions in address order inside a grouped file. Put prototypes in a
header only after the signatures are stable. Keep rows with different compiler
flags in separate units.

## Step 5: verify every readability change

```sh
python tools/match.py > build/match_before.log
# change one name, type, struct, or group only
python tools/match.py > build/match_after.log
```

Both runs must exit 0. Compare:

- the number of rows;
- every row's size;
- the `MATCH` count;
- any new `DIFF` or `BLOCKED` row.

A change that still "looks equivalent" but adds a byte, changes a relocation,
or reports `BLOCKED` is a failed change. Revert that one change; do not weaken
the matcher or edit the target range.

For a grouped translation unit, also verify the whole file and every affected
row. `build/batch/results.tsv` is discovery output, not verification evidence;
only `tools/match.py` is the gate.

## Worked examples

### Constant getter

```c
/* 0x0265FEDC. Role: get_f32_100C92A8 (strong, direct load). */
f32 func_0265FEDC(void) {
    return *(f32 *)0x100C92A8;
}
```

This is a good readability candidate: the load proves the role, and the source
is already small. Four functions load the same address; that is a clone family,
not four different operations.

### Bounded append

```c
void func_02020410(Vec *self, u32 value) {
    if (self->count >= self->capacity) return;
    self->items[self->count] = value;
    self->count = self->count + 1; /* keep the reload */
}
```

The comment on the increment is part of the reconstruction, not decoration.
Changing it can change alias analysis and codegen.

### Named bootstrap function

`runtime_init` and `startup_register` already have names in
`config/symbols.txt`. They are the exception: the name is part of the table
lookup and the evidence is recorded in `docs/BOOTSTRAP.md`. Most functions do
not have that level of support.

### Dispatch shape

```c
if (arg1 == self->field_C) {
    return 0;
}
self->vtable[9]();
return 1;
```

The generated catalog tags only this small shape as `dispatch_vtable_9`. A
large function that merely contains a vtable call is not automatically a
dispatch helper.

## Anti-patterns

- Renaming `func_02020410` in the table without updating every lookup and
  re-running the full matcher.
- Replacing a field with a smaller type to remove a pad.
- Inventing `Vec`, `Node`, `Manager` or `World` names that are not supported by
  the instructions.
- Grouping functions solely because their addresses are adjacent.
- Treating a batch `MATCH` line as permission to skip the full table run.
- Deleting the m2c header before checking that every macro it defines is
  unused.

## Readability checklist

- [ ] The table symbol still matches the source symbol.
- [ ] Compiler flags are unchanged or intentionally isolated.
- [ ] Field offsets, widths and signedness are documented.
- [ ] Every non-obvious temporary has a reason.
- [ ] Absolute data references still resolve to the same address.
- [ ] The full table exits 0 with the same row count.
- [ ] Generated metadata was refreshed with
      `python tools/analyze_structure.py`, if roles or groups changed.
- [ ] The commit describes one readability change or one verified group.
