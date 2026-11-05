#include "block.h"

/* 0x02527114 .. 0x02527158, 18 instructions, 72 bytes. */

extern s32 func_02C72848(u32 *out);
s32 func_02527114(void) {
    u32 value;
    s32 result;

    result = 0;
    value = 0;
    func_02C72848(&value);
    if (value < 0x3C) result = 1;
    return result;
}
