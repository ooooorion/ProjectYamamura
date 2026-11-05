#include "block.h"

/* 0x020A6600 .. 0x020A6610, 5 instructions, 20 bytes.
   Stores the argument at +0x24 and sets bit 2 of the flags word at +0x28;
   see 0x020A65EC. */

typedef struct {
    u8 pad0[0x24];
    s32 field_24;
    s32 flags_28;
} Obj;

void func_020A6600(Obj *self, s32 value) {
    self->field_24 = value;
    self->flags_28 = self->flags_28 | 4;
}
