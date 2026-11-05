#include "block.h"

/* 0x024F0620 .. 0x024F064C, 12 instructions, 48 bytes.
   Reads the indexed masked byte, or 0x7F for a negative index. */

s32 func_024F0620(u8 *base, s32 *arg1) {
    s32 index;
    u8 *entry;

    index = *arg1;
    if (index < 0) return 0x7F;
    entry = base + 0x10;
    if ((u32)index < 0x100U) entry += index;
    return *entry & 0x7F;
}
