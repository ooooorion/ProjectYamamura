#include "block.h"

/* 0x02543A34 .. 0x02543A40, 4 instructions, 16 bytes. */

typedef struct { u8 pad0[0x1AF0]; s32 field_1AF0; s32 field_1AF4; } Obj;
void func_02543A34(Obj *self) {
    self->field_1AF0 = -1;
    self->field_1AF4 = -1;
}
