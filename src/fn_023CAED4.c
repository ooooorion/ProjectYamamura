#include "block.h"

/* 0x023CAED4 .. 0x023CAF04, 13 instructions, 52 bytes.
   Runs the shared setup and the per-object cleanup. */

extern void func_023CACA0(void);
extern void func_023CACEC(s32 arg0);
void func_023CAED4(s32 arg0) {
    func_023CACA0();
    func_023CACEC(arg0);
}
