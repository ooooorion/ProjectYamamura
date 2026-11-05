#include "block.h"

/* 0x023A04C4 .. 0x023A04D0, 4 instructions, 16 bytes.
   Sets the +0x4E54 word to three. */

void func_023A04C4(s32 address) {
    *(s32 *)((u8 *)(address + 0x01A00000) + 0x4E54) = 3;
}
