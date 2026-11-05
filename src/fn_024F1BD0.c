#include "block.h"

/* 0x024F1BD0 .. 0x024F1BD8, 3 instructions, 12 bytes.
   Returns the address of the +0x11F88 table. */

s32 func_024F1BD0(s32 address) {
    return address + 0x11F88;
}
