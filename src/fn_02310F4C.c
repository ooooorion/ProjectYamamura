#include "block.h"

/* 0x02310F4C .. 0x02310FA4, 23 instructions, 92 bytes.
   Runs the final update only when all three guards are clear. */

extern s32 func_02310714(void);
extern s32 func_02310958(s32 arg0);
extern s32 func_02310AD8(s32 arg0);
extern void func_02310CDC(s32 arg0);
void func_02310F4C(s32 arg0) {
    if (func_02310714() == 0 && func_02310958(arg0) == 0 && func_02310AD8(arg0) == 0)
        func_02310CDC(arg0);
}
