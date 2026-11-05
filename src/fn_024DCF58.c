#include "block.h"

/* 0x024DCF58 .. 0x024DCF70, 7 instructions, 28 bytes.
   Copies three words into the +0x114 vector. */

typedef struct { u8 pad0[0x114]; s32 field_114; s32 field_118; s32 field_11C; } Obj;
typedef struct { s32 field_0; s32 field_4; s32 field_8; } Source;
void func_024DCF58(Obj *self, Source *source) {
    self->field_114 = source->field_0;
    self->field_118 = source->field_4;
    self->field_11C = source->field_8;
}
