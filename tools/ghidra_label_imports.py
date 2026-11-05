# Name the targets of Wii U import calls with the SDK function they resolve to.
#
# Reads import_calls.tsv (caller, kind, module, name, stub), decodes the branch at every call
# site in the current program, groups the sites by target, then names each target after its
# import and writes the observed mapping to import_targets.tsv.
#
# The target is read from the program itself, so this works whether the ELF was imported with
# relocations applied or not (the two produce different -- but equally consistent -- targets).
#
# @author buffy
# @category WiiU
# @runtime Jython

import os
from ghidra.program.model.symbol import SourceType

CALLS = os.environ.get("SMM_IMPORT_CALLS", os.path.join("asm", "import_calls.tsv"))
REPORT = os.environ.get("SMM_IMPORT_TARGETS", os.path.join("asm", "import_targets.tsv"))


def log(msg):
    print(msg)


def read_calls(path):
    rows = []
    f = open(path, "r")
    try:
        f.readline()
        for line in f:
            line = line.strip()
            if not line:
                continue
            p = line.split("\t")
            if len(p) < 5:
                continue
            rows.append((int(p[0], 16), p[1], p[2], p[3], int(p[4], 16)))
    finally:
        f.close()
    return rows


def main():
    log("program: %s" % currentProgram.getName())
    rows = read_calls(CALLS)
    log("call sites in table: %d" % len(rows))

    by_target = {}
    missing = 0
    noflow = 0
    for va, kind, module, name, stub in rows:
        ins = getInstructionAt(toAddr(va))
        if ins is None:
            missing += 1
            continue
        flows = ins.getFlows()
        if not flows:
            noflow += 1
            continue
        t = flows[0]
        key = t.getOffset()
        e = by_target.get(key)
        if e is None:
            by_target[key] = [name, module, stub, 1, t]
        else:
            e[3] += 1
            if e[0] != name:
                log("WARN 0x%x reached as %s and %s" % (key, e[0], name))

    log("distinct targets: %d | no instruction: %d | no flow: %d"
        % (len(by_target), missing, noflow))
    if missing:
        log("WARNING: %d call sites not found -- wrong module or build?" % missing)

    created = renamed = labeled = failed = 0
    out = open(REPORT, "w")
    try:
        out.write("name\tmodule\tstub\ttarget\tcalls\n")
        for key in sorted(by_target.keys()):
            name, module, stub, count, t = by_target[key]
            out.write("%s\t%s\t%x\t%x\t%d\n" % (name, module, stub, key, count))
            fn = getFunctionAt(t)
            if fn is not None:
                if fn.getName() != name:
                    fn.setName(name, SourceType.USER_DEFINED)
                    renamed += 1
            else:
                fn = None
                try:
                    fn = createFunction(t, name)
                except Exception:
                    fn = None
                if fn is not None:
                    created += 1
                else:
                    try:
                        createLabel(t, name, True)
                        labeled += 1
                    except Exception:
                        failed += 1
            try:
                setPlateComment(t, "import %s (%s)\nstub 0x%x\n%d call site(s)"
                                % (name, module, stub, count))
            except Exception:
                pass
    finally:
        out.close()

    log("functions created: %d | renamed: %d | label only: %d | failed: %d"
        % (created, renamed, labeled, failed))
    log("report written: %s" % REPORT)


main()
