#include "block.h"

/* 0x024DCF74 .. 0x024DCF78, 2 instructions, 8 bytes.
   Returns the address of the +0x114 vector. */

s32 func_024DCF74(s32 address) {
    return address + 0x114;
}
