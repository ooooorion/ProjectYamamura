#include "block.h"

/* 0x023EEF7C .. 0x023EEFA0, 10 instructions, 40 bytes.
   Stores the flag and records whether it changed from off to on. */

typedef struct { u8 pad0[0x6AE]; u8 field_6AE; s8 field_6AF; } Obj;
void func_023EEF7C(Obj *self, s32 value) {
    s8 changed;
    changed = 0;
    if (value != 0 && self->field_6AE == 0) changed = 1;
    self->field_6AE = (u8)value;
    self->field_6AF = changed;
}
