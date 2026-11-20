// Disable the heavy analyzer that costs the least boundary fidelity.
// Trials: disabling PowerPC Constant Reference loses 544 functions; disabling
// Stack loses only 1. Keep the PPC analyzer and disable Stack so the run still
// finishes under the 1800s cap with the function set intact.
// Function discovery, disassembly, and function creation remain enabled.
// @category ProjectYamamura
import ghidra.app.plugin.core.analysis.AutoAnalysisManager;
import ghidra.app.script.GhidraScript;
import ghidra.framework.options.Options;

public class DisableHeavyAnalyzers extends GhidraScript {
    private static final String[] HEAVY = {
        "Stack"
    };

    @Override
    public void run() throws Exception {
        AutoAnalysisManager manager =
            AutoAnalysisManager.getAnalysisManager(currentProgram);
        Options options = currentProgram.getOptions("Analyzers");
        for (String name : HEAVY) {
            boolean present = options.contains(name);
            boolean before = present && options.getBoolean(name, true);
            if (present) {
                options.setBoolean(name, false);
            }
            println("analyzer " + name + ": present=" + present
                + " enabled-before=" + before
                + " enabled-after=" + (present && options.getBoolean(name, true)));
        }
        // Apply the changed flags to the scheduler tasks before analysis starts.
        manager.initializeOptions(options);
    }
}
