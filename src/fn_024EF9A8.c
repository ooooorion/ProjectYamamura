#include "block.h"

/* 0x024EF9A8 .. 0x024EF9C4, 8 instructions, 32 bytes.
   Reads the indexed byte after +0x110, with a 256-entry bound. */

s8 func_024EF9A8(u8 *base, u32 *arg1) {
    u32 index;
    u8 *entry;

    index = *arg1;
    entry = base + 0x110;
    if (index < 0x100U) entry += index;
    return (s8)*entry;
}
