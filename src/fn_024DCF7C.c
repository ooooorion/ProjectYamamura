#include "block.h"

/* 0x024DCF7C .. 0x024DCF94, 7 instructions, 28 bytes.
   Copies three words into the +0x120 vector. */

typedef struct { u8 pad0[0x120]; s32 field_120; s32 field_124; s32 field_128; } Obj;
typedef struct { s32 field_0; s32 field_4; s32 field_8; } Source;
void func_024DCF7C(Obj *self, Source *source) {
    self->field_120 = source->field_0;
    self->field_124 = source->field_4;
    self->field_128 = source->field_8;
}
