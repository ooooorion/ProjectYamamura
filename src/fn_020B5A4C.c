#include "block.h"

/* 0x020B5A4C .. 0x020B5A54, 2 instructions, 8 bytes.
   Returns the float constant at 0x10012868; see 0x020B5A40. */

f32 func_020B5A4C(void) {
    return *(f32 *)0x10012868;
}
