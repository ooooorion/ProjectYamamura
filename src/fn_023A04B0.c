#include "block.h"

/* 0x023A04B0 .. 0x023A04C0, 5 instructions, 20 bytes.
   Stores a byte and sets the +0x4E54 word to two. */

void func_023A04B0(s32 address, s8 value) {
    void *base = (void *)(address + 0x01A00000);
    *(s8 *)((u8 *)base + 0x4E64) = value;
    *(s32 *)((u8 *)base + 0x4E54) = 2;
}
