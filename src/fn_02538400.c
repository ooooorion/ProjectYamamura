#include "block.h"

/* 0x02538400 .. 0x02538430, 13 instructions, 52 bytes. */

extern s32 func_02538104(s32 value);
extern s32 func_0270A8F0(s32 value);
void func_02538400(s32 arg0) {
    func_02538104(arg0 + 8);
    func_0270A8F0(*(s32 *)((u8 *)*(void **)0x10189600 + 0x20));
}
