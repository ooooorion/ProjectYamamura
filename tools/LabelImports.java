// Name the targets of Wii U import calls with the SDK function they resolve to.
//
// The mapping import -> target comes from import_targets_expected.tsv, decoded offline from the
// ELF's own R_PPC_REL24 displacements. The program is used only to verify that mapping, so a
// call site Ghidra never disassembled costs nothing: every one of the 594 imports still gets a
// name, because the target is a property of the import, not of the call site.
//
// Detects automatically whether the program was imported with "Perform Symbol Relocations":
// raw targets are 0x02C6E2A8+, relocated ones collapse to stub - 0xC0000000 (0x006348..0x0079D0).
// Both are named correctly.
//
//@author buffy
//@category WiiU

import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.symbol.SourceType;

public class LabelImports extends GhidraScript {

	private static final String ASM_DIR = System.getProperty("smm.asm", "asm");
	private static final String EXPECTED = Paths.get(ASM_DIR, "import_targets_expected.tsv").toString();
	private static final String CALLS = Paths.get(ASM_DIR, "import_calls.tsv").toString();
	private static final String REPORT = Paths.get(ASM_DIR, "import_targets.tsv").toString();
	private static final String MISSING = Paths.get(ASM_DIR, "import_missing_sites.txt").toString();
	private static final long STUB_BASE = 0xC0000000L;

	private static final class Imp {
		final String name;
		final String module;
		final long stub;
		final long raw;
		final int calls;

		Imp(String name, String module, long stub, long raw, int calls) {
			this.name = name;
			this.module = module;
			this.stub = stub;
			this.raw = raw;
			this.calls = calls;
		}

		long target(boolean useRaw) {
			return useRaw ? raw : stub - STUB_BASE;
		}
	}

	@Override
	public void run() throws Exception {
		println("program: " + currentProgram.getName());

		List<Imp> imports = new ArrayList<>();
		Map<Long, Imp> byStub = new TreeMap<>();
		List<String> lines = Files.readAllLines(Paths.get(EXPECTED), StandardCharsets.UTF_8);
		for (int i = 1; i < lines.size(); i++) {
			String line = lines.get(i).trim();
			if (line.isEmpty()) {
				continue;
			}
			String[] p = line.split("\t");
			if (p.length < 5) {
				continue;
			}
			Imp imp = new Imp(p[0], p[1], Long.parseLong(p[2], 16), Long.parseLong(p[3], 16),
				Integer.parseInt(p[4].trim()));
			imports.add(imp);
			byStub.put(imp.stub, imp);
		}
		println("imports in table: " + imports.size());

		List<String> callLines = Files.readAllLines(Paths.get(CALLS), StandardCharsets.UTF_8);
		int total = 0;
		int noIns = 0;
		int rawHit = 0;
		int colHit = 0;
		int neither = 0;

		try (BufferedWriter miss = Files.newBufferedWriter(Paths.get(MISSING),
			StandardCharsets.US_ASCII)) {
			for (int i = 1; i < callLines.size(); i++) {
				String line = callLines.get(i).trim();
				if (line.isEmpty()) {
					continue;
				}
				String[] p = line.split("\t");
				if (p.length < 5) {
					continue;
				}
				total++;

				long va = Long.parseLong(p[0], 16);
				long stub = Long.parseLong(p[4], 16);

				Instruction ins = getInstructionAt(toAddr(va));
				Address t = null;
				if (ins != null) {
					Address[] flows = ins.getFlows();
					if (flows != null && flows.length > 0) {
						t = flows[0];
					}
				}
				if (t == null) {
					noIns++;
					miss.write(String.format("%08x\t%s\t%s\n", va, p[3], p[4]));
					continue;
				}

				long got = t.getOffset();
				Imp imp = byStub.get(stub);
				if (imp != null && got == imp.raw) {
					rawHit++;
				}
				else if (got == stub - STUB_BASE) {
					colHit++;
				}
				else {
					neither++;
				}
			}
		}

		println("call sites: " + total + " | decoded: " + (total - noIns) + " | no instruction: "
			+ noIns);
		boolean useRaw = rawHit >= colHit;
		println("target check: raw " + rawHit + " | collapsed " + colHit + " | neither " + neither
			+ " -> " + (useRaw ? "raw" : "collapsed") + " targets");

		long min = Long.MAX_VALUE;
		long max = Long.MIN_VALUE;
		for (Imp imp : imports) {
			long t = imp.target(useRaw);
			min = Math.min(min, t);
			max = Math.max(max, t);
		}

		Memory mem = currentProgram.getMemory();
		if (!mem.contains(toAddr(min))) {
			String blockName = useRaw ? "import_stubs" : "import_stubs_relocated";
			long size = max - min + 16;
			try {
				MemoryBlock block = mem.createUninitializedBlock(blockName, toAddr(min), size, false);
				block.setExecute(true);
				println("created block " + blockName + " at " + toAddr(min) + " size 0x"
					+ Long.toHexString(size));
			}
			catch (Exception ex) {
				println("could not create stub block: " + ex.getMessage());
			}
		}
		else {
			println("stub window already mapped: " + toAddr(min));
		}

		int created = 0;
		int renamed = 0;
		int labeled = 0;
		int failed = 0;

		Path report = Paths.get(REPORT);
		try (BufferedWriter out = Files.newBufferedWriter(report, StandardCharsets.US_ASCII)) {
			out.write("name\tmodule\tstub\ttarget\tcalls\n");
			for (Imp imp : imports) {
				long tv = imp.target(useRaw);
				Address t = toAddr(tv);
				out.write(imp.name + "\t" + imp.module + "\t" + Long.toHexString(imp.stub) + "\t"
					+ Long.toHexString(tv) + "\t" + imp.calls + "\n");

				Function fn = getFunctionAt(t);
				if (fn != null) {
					if (!fn.getName().equals(imp.name)) {
						fn.setName(imp.name, SourceType.USER_DEFINED);
						renamed++;
					}
				}
				else {
					try {
						fn = createFunction(t, imp.name);
					}
					catch (Exception ex) {
						fn = null;
					}
					if (fn != null) {
						created++;
					}
					else {
						try {
							createLabel(t, imp.name, true);
							labeled++;
						}
						catch (Exception ex) {
							failed++;
						}
					}
				}

				try {
					setPlateComment(t, "import " + imp.name + " (" + imp.module + ")\nstub 0x"
						+ Long.toHexString(imp.stub) + "\n" + imp.calls + " call site(s)");
				}
				catch (Exception ex) {
					// cosmetic only
				}
			}
		}

		println("functions created: " + created + " | renamed: " + renamed + " | label only: "
			+ labeled + " | failed: " + failed);
		println("undecoded call sites written to " + MISSING);
		println("report written to " + REPORT);
	}
}
