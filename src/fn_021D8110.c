#include "block.h"

/* 0x021D8110 .. 0x021D8118, 3 instructions, 12 bytes.
   Returns the float at 0x100380EC. */

f32 func_021D8110(void) { return *(f32 *)0x100380EC; }
