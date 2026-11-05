# Repository policy

This repository is intended to be public. It contains documentation, reconstructed source,
configuration, and tooling for a research decompilation. It is not a build of
the game and cannot produce a playable executable.

## What must never be committed

- Any game asset, disc image, extracted data tree, `.rpx`/`.rpl`, or executable.
- Any encryption, title, or common key.
- Any Nintendo SDK, Green Hills compiler, licence file, or licence-server
  configuration.
- Any generated disassembly under `asm/`, build output under `build/`, or
  extracted trees under `orig/`.
- Any personal path, serial, host identifier, or credential.

`.gitignore` enforces most of this. It is a safety net, not a substitute for
reviewing `git status` before every commit.

## History is public and permanent

Deleting a file in a later commit does not remove it from history. A key or a
game binary that lands in one commit is present in every clone. Before
publishing or force-pushing:

- scan the full history, not only the current tree;
- if a secret is found, rotate or revoke it, then rewrite history (for example
  with `git filter-repo`) or publish a fresh repository from a clean tree;
- enable GitHub secret scanning and push protection.

A history rewrite changes every affected SHA and requires a force-push. Do not
do it casually on a repository others have cloned.

## Layout

```
include/    reconstructed headers
src/        matched C, one function per file; near misses in src/near/
config/     symbols, splits, and generated evidence tables
docs/       extraction, provenance, decompilation notes, roadmap
tools/      indexer, labeler, slicer, matcher, analyzer
```

## Licensing

`tools/` and `docs/` are MIT; see `LICENSE`. The reconstructed source under
`src/` is a derivative work of the original program and carries no licence to
the underlying work; see `LICENSE-DECOMPILED`. Research and interoperability
study only.

## Verification

There is no CI. Byte matching needs a licensed GHS `ccppc` 5.3.27 and the
retail ELF, neither of which can run in a public runner. Verification is local:
`python tools/match.py` exits non-zero on any byte or size difference.

## Commit discipline

- Keep one commit per matched function or coherent batch, with the address in
  the subject.
- Never `git add -A`; review `git status` and stage explicit paths.
- Do not commit generated `asm/`, `build/`, or `orig/` content.
- Regenerate the structure catalogs after table changes.

## Public-release checklist

- [ ] `git status` clean; no game data or keys staged
- [ ] full history scanned for keys, serials, personal paths, and binaries
- [ ] any exposed credential rotated or revoked
- [ ] README legal and provenance sections current
- [ ] GitHub secret scanning and push protection enabled
