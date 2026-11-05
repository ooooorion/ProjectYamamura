#include "block.h"

/* 0x0215F510 .. 0x0215F518, 3 instructions, 12 bytes.
   Stores the constant 0x70 at +0x0C and returns nothing. */

typedef struct {
    u8 pad0[0xC];
    s32 field_C;
} Obj;

void func_0215F510(Obj *self) {
    self->field_C = 0x70;
}
