#include "block.h"

/* 0x021F6BB8 .. 0x021F6BF0, 15 instructions, 60 bytes.
   Runs the no-argument setup helper, then forwards this object and the shared
   float at 0x1003CD9C to the second helper. */

extern void func_021F6AA0(void);
extern void func_021F674C(s32 arg0, f32 value);

void func_021F6BB8(s32 arg0) {
    func_021F6AA0();
    func_021F674C(arg0, *(f32 *)0x1003CD9C);
}
