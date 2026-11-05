#include "block.h"

/* 0x02077068 .. 0x02077074, 4 instructions, 16 bytes.
   Reads +0x250 of the object published through the global pointer at
   0x1018953C; see 0x020768EC. */

s32 func_02077068(void) {
    return *(s32 *)((u8 *)*(void **)0x1018953C + 0x250);
}
