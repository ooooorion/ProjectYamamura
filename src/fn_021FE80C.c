#include "block.h"

/* 0x021FE80C .. 0x021FE814, 3 instructions, 12 bytes.
   Returns the float at 0x1003D700. */

f32 func_021FE80C(void) { return *(f32 *)0x1003D700; }
