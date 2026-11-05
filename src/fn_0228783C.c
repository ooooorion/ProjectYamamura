#include "block.h"

/* 0x0228783C .. 0x0228785C, 9 instructions, 36 bytes.
   Selects one of two constants for state 3. */

f32 func_0228783C(s32 *state) {
    if (*state == 3) return *(f32 *)0x10051D10;
    return *(f32 *)0x10051C54;
}
