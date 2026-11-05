#include "block.h"

/* 0x021E8148 .. 0x021E8178, 13 instructions, 52 bytes.
   Runs the no-argument setup helper, then forwards this object to the second
   helper. */

extern void func_021E7C60(void);
extern void func_021E80A8(s32 arg0);

void func_021E8148(s32 arg0) {
    func_021E7C60();
    func_021E80A8(arg0);
}
