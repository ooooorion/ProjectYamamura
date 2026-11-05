#include "block.h"

/* 0x020547A8 .. 0x020547AC, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 8; see 0x02054798. */

s32 func_020547A8(s32 value) {
    return value + 8;
}
