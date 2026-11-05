#include "block.h"

/* 0x023EEF54 .. 0x023EEF78, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x6AC]; u8 field_6AC; s8 field_6AD; } Obj;
void func_023EEF54(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_6AC == 0) changed = 1;
    self->field_6AC = (u8)value;
    self->field_6AD = changed;
}
