#include "block.h"

/* 0x021D811C .. 0x021D8124, 3 instructions, 12 bytes.
   Returns the float at 0x100380F0. */

f32 func_021D811C(void) { return *(f32 *)0x100380F0; }
