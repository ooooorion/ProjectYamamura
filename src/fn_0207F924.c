#include "block.h"

/* 0x0207F924 .. 0x0207F928, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 0x18. */

s32 func_0207F924(s32 value) {
    return value + 0x18;
}
