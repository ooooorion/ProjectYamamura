#include "block.h"

/* 0x023F01D4 .. 0x023F01F8, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x69D]; u8 field_69D; s8 field_69E; } Obj;
void func_023F01D4(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_69D == 0) changed = 1;
    self->field_69D = (u8)value;
    self->field_69E = changed;
}
