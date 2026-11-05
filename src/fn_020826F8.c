#include "block.h"

/* 0x020826F8 .. 0x020826FC, 2 instructions, 8 bytes.
   Plain store through the first argument. */

void func_020826F8(s32 *target, s32 value) {
    *target = value;
}
