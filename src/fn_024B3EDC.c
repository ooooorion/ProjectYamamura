#include "block.h"

/* 0x024B3EDC .. 0x024B3EF4, 7 instructions, 28 bytes.
   Copies three words into the +0x240 vector. */

typedef struct { u8 pad0[0x240]; s32 field_240; s32 field_244; s32 field_248; } Obj;
typedef struct { s32 field_0; s32 field_4; s32 field_8; } Source;
void func_024B3EDC(Obj *self, Source *source) {
    self->field_240 = source->field_0;
    self->field_244 = source->field_4;
    self->field_248 = source->field_8;
}
