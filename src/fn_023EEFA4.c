#include "block.h"

/* 0x023EEFA4 .. 0x023EEFC8, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x6B5]; u8 field_6B5; s8 field_6B6; } Obj;
void func_023EEFA4(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_6B5 == 0) changed = 1;
    self->field_6B5 = (u8)value;
    self->field_6B6 = changed;
}
