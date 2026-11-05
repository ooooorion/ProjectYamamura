#include "block.h"

/* 0x02287880 .. 0x022878A0, 9 instructions, 36 bytes.
   Selects one of two constants for state 3. */

f32 func_02287880(s32 *state) {
    if (*state == 3) return *(f32 *)0x10051D14;
    return *(f32 *)0x10051D18;
}
