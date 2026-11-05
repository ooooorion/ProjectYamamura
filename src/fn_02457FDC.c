#include "block.h"

/* 0x02457FDC .. 0x0245801C, 17 instructions, 68 bytes.
   Runs the type-7 transition and marks the object ready. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; u8 pad1EC[0x1A66]; s8 field_1C52; } Obj;
extern void func_02457D40(Obj *self);
void func_02457FDC(Obj *self) {
    if (self->field_1E8 == 7) func_02457D40(self);
    self->field_1C52 = 1;
}
