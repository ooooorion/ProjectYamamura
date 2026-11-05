#include "block.h"

/* 0x02344A90 .. 0x02344AA8, 7 instructions, 28 bytes.
   Returns +0x3C or falls back to +0x28. */

typedef struct { u8 pad0[0x28]; s32 field_28; u8 pad2C[0x10]; s32 field_3C; } Obj;
s32 func_02344A90(Obj *self) {
    s32 value = self->field_3C;
    if (value != 0) return value;
    return self->field_28;
}
