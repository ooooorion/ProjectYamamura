#include "block.h"

/* 0x023EEF04 .. 0x023EEF28, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x699]; u8 field_699; s8 field_69A; } Obj;
void func_023EEF04(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_699 == 0) changed = 1;
    self->field_699 = (u8)value;
    self->field_69A = changed;
}
