#include "block.h"

/* 0x024F1344 .. 0x024F1368, 10 instructions, 40 bytes.
   Stores into the bounded 4x3 byte table at +0x327. */

void func_024F1344(u8 *base, u32 arg1, u32 arg2, s8 value) {
    s8 *entry;

    entry = (s8 *)(base + 0x327);
    if (arg1 < 4U) entry += arg1 * 3;
    if (arg2 < 3U) entry += arg2;
    *entry = value;
}
