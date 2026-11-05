#include "block.h"

/* 0x024DF754 .. 0x024DF778, 10 instructions, 40 bytes.
   Tracks the transition into a nonzero state at +0x31. */

typedef struct { u8 pad0[0x31]; s8 field_31; u8 field_32; } Obj;
void func_024DF754(Obj *self, s32 arg1) {
    s8 active;

    active = 0;
    if (arg1 != 0 && self->field_32 == 0) active = 1;
    self->field_32 = (u8)arg1;
    self->field_31 = active;
}
