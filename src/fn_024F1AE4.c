#include "block.h"

/* 0x024F1AE4 .. 0x024F1AF8, 6 instructions, 24 bytes.
   Reads the bounded four-entry byte table at +0x2F0. */

u8 func_024F1AE4(u8 *base, u32 index) {
    u8 *entry;

    entry = base + 0x2F0;
    if (index < 4U) entry += index;
    return *entry;
}
