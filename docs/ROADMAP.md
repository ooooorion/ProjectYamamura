# Roadmap

One person, one list.

| # | Milestone | State |
|---|---|---|
| 1 | Toolchain validated: ELF extracted, sections sane, disassembly greppable | done |
| 2 | Entry point identified: say what `main` is | done -- `_start` at `0x02B8AECC`, see `BOOTSTRAP.md` |
| 3 | First subsystem mapped | done -- bootstrap chain and constructor table, see `BOOTSTRAP.md` |
| 4 | First function fully matched | done -- 1,638, see `DECOMPILATION.md` |
| 5 | `config/symbols.txt` above 100 entries | 63 |
| 6 | One subsystem reconstructed end to end | not started |
| 7 | Bulk-decompile every start (year-end goal) | not started |

## Current position

1,638 functions matched (78,948 bytes, 6.01% of the 27,267 starts) and 2,008
near misses archived. The bootstrap chain is mapped; both runtime helpers
match, while `__init` does not.

## Next

- Continue the leaf-first, call-aware sweep from `0x029D8000` in 16 KB bands.
- Revisit the closest call-bearing near misses. The dropped-argument,
  absolute-address and `rlwinm`-allocation patterns have been productive.
- Keep `__init` as the outstanding bootstrap target.
- Pilot one readability group from `docs/FUNCTION_GROUPS.md`, starting with
  address getters or constant returns, and re-run the full table.
- Replace the `bl`-target extent heuristic with a Ghidra export.
- Name the 21 internal callees of `main`, starting with `0x0276FBA4`.
- The year-end bulk-decompile goal needs a headless export over all 27,267
  starts, with the 1,638 matched functions kept as the verified core.

Step 4 was taken before step 3 on purpose: the toolchain had to be proven
before subsystem work was worth doing. With 1,638 matches, the bootstrap
subsystem now has its first reconstruction.
