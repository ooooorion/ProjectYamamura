#include "block.h"

/* 0x023050D8 .. 0x02305110, 15 instructions, 60 bytes.
   Passes the +0x39C word through an import call. */

extern void func_020A1E90(s32 arg0, s32 *arg1);
void func_023050D8(void *self) {
    s32 sp8 = *(s32 *)((u8 *)self + 0x39C);
    func_020A1E90(*(s32 *)0x10182874 + 0x52A58, &sp8);
}
