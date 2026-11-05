#include "block.h"

/* 0x024CB118 .. 0x024CB12C, 6 instructions, 24 bytes.
   Reads the indexed byte after +0x11E0, with a 100-entry bound. */

u8 func_024CB118(u8 *base, u32 index) {
    u8 *entry;

    entry = base + 0x11E0;
    if (index < 0x64U) entry += index;
    return *entry;
}
