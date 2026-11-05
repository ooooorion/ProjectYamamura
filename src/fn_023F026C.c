#include "block.h"

/* 0x023F026C .. 0x023F0290, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x69F]; u8 field_69F; s8 field_6A0; } Obj;
void func_023F026C(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_69F == 0) changed = 1;
    self->field_69F = (u8)value;
    self->field_6A0 = changed;
}
