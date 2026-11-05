#include "block.h"

/* 0x02537560 .. 0x02537584, 10 instructions, 40 bytes. */

typedef struct { u8 pad0[0x14]; s32 field_14; u8 pad18[4]; s32 field_1C; } Obj;
s32 func_02537560(Obj *self) {
    s32 result;

    result = 0;
    if (self->field_14 != 0 && self->field_1C != -1) result = 1;
    return result;
}
