#include "block.h"

/* 0x020547B0 .. 0x020547B4, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 8; see 0x02054798. */

s32 func_020547B0(s32 value) {
    return value + 8;
}
