#include "block.h"

/* 0x0236D064 .. 0x0236D068, 2 instructions, 8 bytes.
   Masks the low bit. */

s32 func_0236D064(s32 value) { return value & 1; }
