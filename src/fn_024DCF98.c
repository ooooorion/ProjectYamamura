#include "block.h"

/* 0x024DCF98 .. 0x024DCF9C, 2 instructions, 8 bytes.
   Returns the address of the +0x120 vector. */

s32 func_024DCF98(s32 address) {
    return address + 0x120;
}
