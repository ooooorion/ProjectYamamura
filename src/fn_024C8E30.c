#include "block.h"

/* 0x024C8E30 .. 0x024C8E48, 7 instructions, 28 bytes.
   Reads the indexed 0x2C-byte record byte, with a 100-entry bound. */

u8 func_024C8E30(u8 *base, u32 index) {
    u8 *entry;

    entry = base + 0xB0;
    if (index < 0x64U) entry += index * 0x2C;
    return *entry;
}
