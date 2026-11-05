#include "block.h"

/* 0x024C7354 .. 0x024C7374, 9 instructions, 36 bytes.
   Copies two vectors into the +0x80 block. */

typedef struct { f32 field_0; f32 field_4; } Vec2;
typedef struct {
    u8 pad0[0x80];
    f32 field_80;
    f32 field_84;
    f32 field_88;
    f32 field_8C;
} Obj;
void func_024C7354(Obj *self, Vec2 *arg1, Vec2 *arg2) {
    self->field_80 = arg1->field_0;
    self->field_84 = arg1->field_4;
    self->field_88 = arg2->field_0;
    self->field_8C = arg2->field_4;
}
