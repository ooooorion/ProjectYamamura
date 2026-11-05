#include "block.h"

/* 0x023EEF2C .. 0x023EEF50, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x69B]; u8 field_69B; s8 field_69C; } Obj;
void func_023EEF2C(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_69B == 0) changed = 1;
    self->field_69B = (u8)value;
    self->field_69C = changed;
}
