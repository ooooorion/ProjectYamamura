#include "block.h"

/* 0x020768EC .. 0x020768F8, 4 instructions, 16 bytes.
   Reads +0x254 of the object published through the global pointer at
   0x1018953C. The sibling at 0x02077068 reads +0x250. */

s32 func_020768EC(void) {
    return *(s32 *)((u8 *)*(void **)0x1018953C + 0x254);
}
