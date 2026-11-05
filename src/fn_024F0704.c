#include "block.h"

/* 0x024F0704 .. 0x024F0720, 8 instructions, 32 bytes.
   Returns the high bit of the indexed byte. */

s32 func_024F0704(u8 *base, u32 *arg1) {
    u32 index;
    u8 *entry;

    index = *arg1;
    entry = base + 0x10;
    if (index < 0x100U) entry += index;
    return ((u8)*entry >> 7U) & 1;
}
