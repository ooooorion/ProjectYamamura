#include "block.h"

/* 0x02241F7C .. 0x02241FA4, 11 instructions, 44 bytes.
   Returns whether the object's +0x14 field compares equal to zero. */

extern s32 func_020CF6FC(s32 value);

s32 func_02241F7C(s32 arg0) {
    return func_020CF6FC(arg0 + 0x14) == 0;
}
