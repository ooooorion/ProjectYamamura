#include "block.h"

/* 0x02146950 .. 0x0214695C, 4 instructions, 16 bytes.
   Clears +0x504 then +0x500 in the target's store order. */

typedef struct {
    u8 pad0[0x500];
    s32 field_500;
    s32 field_504;
} Obj;

void func_02146950(Obj *self) {
    self->field_504 = 0;
    self->field_500 = 0;
}
