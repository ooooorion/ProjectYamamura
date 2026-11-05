#include "block.h"

/* 0x022C9C58 .. 0x022C9C6C, 6 instructions, 24 bytes.
   Stores an id and two copies of a float constant. */

typedef struct { u8 pad0[0x7C]; s32 field_7C; f32 field_80; f32 field_84; } Obj;
void func_022C9C58(Obj *self, s32 arg1) {
    f32 value = *(f32 *)0x100593C8;
    self->field_7C = arg1;
    self->field_80 = value;
    self->field_84 = value;
}
