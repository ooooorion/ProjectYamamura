#include "block.h"

/* 0x0235D7D0 .. 0x0235D7D4, 2 instructions, 8 bytes.
   Masks the low nibble. */

s32 func_0235D7D0(s32 value) { return value & 0xF; }
