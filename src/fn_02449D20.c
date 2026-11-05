#include "block.h"

/* 0x02449D20 .. 0x02449D40, 9 instructions, 36 bytes.
   True when the shared global state value is two. */

s32 func_02449D20(void) {
    s32 *value;
    value = *(s32 **)((u8 *)*(void **)0x10187184 + 0x12068);
    return (*value ^ 2) == 0;
}
