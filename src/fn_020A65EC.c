#include "block.h"

/* 0x020A65EC .. 0x020A65FC, 5 instructions, 20 bytes.
   Stores the argument at +0x20 and sets bit 1 of the flags word at +0x28;
   0x020A6600 does the same at +0x24 with bit 2. */

typedef struct {
    u8 pad0[0x20];
    s32 field_20;
    u8 pad_24[4];
    s32 flags_28;
} Obj;

void func_020A65EC(Obj *self, s32 value) {
    self->field_20 = value;
    self->flags_28 = self->flags_28 | 2;
}
