#include "block.h"

/* 0x0249C5C8 .. 0x0249C5EC, 10 instructions, 40 bytes.
   Tracks the transition into a nonzero state. */

typedef struct { u8 pad0[0x368]; s8 field_368; u8 field_369; } Obj;
void func_0249C5C8(Obj *self, s32 arg1) {
    s8 active;

    active = 0;
    if (arg1 != 0 && self->field_369 == 0) active = 1;
    self->field_368 = active;
    self->field_369 = (u8)arg1;
}
