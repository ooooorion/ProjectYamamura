#include "block.h"

/* 0x025242C8 .. 0x025242D8, 5 instructions, 20 bytes. */

typedef struct { u8 pad0[0x28]; s32 field_28; s32 field_2C; u8 pad30[0xA8]; u8 field_D8; } Obj;
void func_025242C8(Obj *self) {
    self->field_28 = 0;
    self->field_2C = 0;
    self->field_D8 = 0;
}
