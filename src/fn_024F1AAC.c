#include "block.h"

/* 0x024F1AAC .. 0x024F1AC0, 6 instructions, 24 bytes.
   Stores into the bounded four-entry byte table at +0x2F0. */

void func_024F1AAC(u8 *base, u32 index, s8 value) {
    s8 *entry;

    entry = (s8 *)(base + 0x2F0);
    if (index < 4U) entry += index;
    *entry = value;
}
