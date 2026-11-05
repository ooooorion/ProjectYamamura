#include "block.h"

/* 0x02054798 .. 0x0205479C, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 8. The identical body appears
   at 0x020547A0, 0x020547A8 and 0x020547B0. */

s32 func_02054798(s32 value) {
    return value + 8;
}
