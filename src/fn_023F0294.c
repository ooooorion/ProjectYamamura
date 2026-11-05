#include "block.h"

/* 0x023F0294 .. 0x023F02B8, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x6A1]; u8 field_6A1; s8 field_6A2; } Obj;
void func_023F0294(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_6A1 == 0) changed = 1;
    self->field_6A1 = (u8)value;
    self->field_6A2 = changed;
}
