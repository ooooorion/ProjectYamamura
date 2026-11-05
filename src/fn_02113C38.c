#include "block.h"

/* 0x02113C38 .. 0x02113C3C, 2 instructions, 8 bytes.
   Moves the low half-word into the high half. */

s32 func_02113C38(s32 value) {
    return value << 16;
}
