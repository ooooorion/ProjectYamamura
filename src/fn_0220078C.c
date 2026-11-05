#include "block.h"

/* 0x0220078C .. 0x022007C0, 14 instructions, 56 bytes.
   Refreshes the shared state, then registers the supplied value with flag 1. */

extern void func_02200484(void);
extern void func_022006DC(s32 value, s32 flag);

void func_0220078C(s32 arg0) {
    func_02200484();
    func_022006DC(arg0, 1);
}
