#include "block.h"

/* 0x02467B7C .. 0x02467BA4, 11 instructions, 44 bytes.
   Looks up the indexed value, defaulting to four when out of range. */

typedef struct { u8 pad0[0x2B0]; s32 field_2B0; } Obj;
s32 func_02467B7C(Obj *self, s32 arg1) {
    s32 result;
    result = 4;
    if (arg1 < 4) result = *(s32 *)((u8 *)((((self->field_2B0 * 4) + arg1) * 4) + 0x10090000) - 0x35B4);
    return result;
}
