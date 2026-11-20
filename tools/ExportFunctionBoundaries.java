// Export every analyzed function whose entry point is inside .text.
// @category ProjectYamamura
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.mem.MemoryBlock;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class ExportFunctionBoundaries extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) {
            throw new IllegalArgumentException(
                "usage: ExportFunctionBoundaries.java <output.tsv>");
        }

        MemoryBlock text = currentProgram.getMemory().getBlock(".text");
        if (text == null) {
            throw new IllegalStateException("program has no .text block");
        }
        Address textStart = text.getStart();
        Address textEnd = text.getEnd();

        FunctionManager functions = currentProgram.getFunctionManager();
        List<Function> selected = new ArrayList<>();
        for (Function function : functions.getFunctions(true)) {
            Address entry = function.getEntryPoint();
            if (entry == null || entry.compareTo(textStart) < 0 ||
                    entry.compareTo(textEnd) > 0 || function.isExternal()) {
                continue;
            }
            selected.add(function);
        }
        selected.sort(Comparator.comparing(Function::getEntryPoint));

        File output = new File(args[0]).getAbsoluteFile();
        File parent = output.getParentFile();
        if (parent != null) {
            parent.mkdirs();
        }
        try (PrintWriter out = new PrintWriter(
                new BufferedWriter(new FileWriter(output)))) {
            out.println("entry\tmin\tmax\tbytes\tranges\tname\tnamespace\t"
                    + "thunk\texternal\tfragmented\tparams\tcc");
            for (Function function : selected) {
                AddressSetView body = function.getBody();
                Address min = body.getMinAddress();
                Address max = body.getMaxAddress();
                if (min == null || max == null) {
                    continue;
                }
                Address entry = function.getEntryPoint();
                String namespace = function.getParentNamespace() == null
                        ? "" : function.getParentNamespace().getName(true);
                String cc = function.getCallingConventionName();
                out.printf("%08X\t%08X\t%08X\t%d\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%s%n",
                        entry.getOffset(), min.getOffset(), max.getOffset(),
                        body.getNumAddresses(), body.getNumAddressRanges(),
                        clean(function.getName()), clean(namespace),
                        function.isThunk() ? 1 : 0,
                        function.isExternal() ? 1 : 0,
                        body.getNumAddressRanges() > 1 ? 1 : 0,
                        function.getParameterCount(), clean(cc));
            }
        }
        println("exported " + selected.size() + " functions to " + output);
    }

    private static String clean(String value) {
        if (value == null) {
            return "";
        }
        return value.replace('\t', ' ').replace('\r', ' ').replace('\n', ' ');
    }
}
