#include "block.h"

/* 0x0207C9E8 .. 0x0207C9EC, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 8; see 0x0207C514. */

s32 func_0207C9E8(s32 value) {
    return value + 8;
}
