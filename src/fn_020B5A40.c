#include "block.h"

/* 0x020B5A40 .. 0x020B5A48, 2 instructions, 8 bytes.
   Returns the float constant at 0x10012864; 0x020B5A4C reads 0x10012868. */

f32 func_020B5A40(void) {
    return *(f32 *)0x10012864;
}
