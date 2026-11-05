#include "block.h"

/* 0x021C7C18 .. 0x021C7C50, 15 instructions, 60 bytes.
   Clears the +0x114 subobject, then runs the object cleanup helper. */

extern void func_021EF7FC(s32 arg0, s32 arg1);
extern void func_021BD9D0(s32 arg0);

void func_021C7C18(s32 arg0) {
    func_021EF7FC(arg0 + 0x114, 0);
    func_021BD9D0(arg0);
}
