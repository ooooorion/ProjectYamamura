#include "block.h"

/* 0x023EF094 .. 0x023EF0B8, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x6BF]; u8 field_6BF; s8 field_6C0; } Obj;
void func_023EF094(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_6BF == 0) changed = 1;
    self->field_6BF = (u8)value;
    self->field_6C0 = changed;
}
