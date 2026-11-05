#include "block.h"

/* 0x024CB1B8 .. 0x024CB1E8, 13 instructions, 52 bytes.
   Copies six floats into the +0x44 block. */

typedef struct {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    f32 field_C;
    f32 field_10;
    f32 field_14;
} Source;
typedef struct {
    u8 pad0[0x44];
    f32 field_44;
    f32 field_48;
    f32 field_4C;
    f32 field_50;
    f32 field_54;
    f32 field_58;
} Obj;
void func_024CB1B8(Obj *self, Source *source) {
    self->field_44 = source->field_0;
    self->field_48 = source->field_4;
    self->field_4C = source->field_8;
    self->field_50 = source->field_C;
    self->field_54 = source->field_10;
    self->field_58 = source->field_14;
}
