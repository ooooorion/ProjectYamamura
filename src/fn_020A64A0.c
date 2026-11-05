#include "block.h"

/* 0x020A64A0 .. 0x020A64B4, 6 instructions, 24 bytes.
   Stores the two arguments at +0x1C and +0x18 (reverse order) and sets bit 0
   of the flags word at +0x28. */

typedef struct {
    u8 pad0[0x18];
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 flags_28;
} Obj;

void func_020A64A0(Obj *self, s32 first, s32 second) {
    self->field_1C = second;
    self->field_18 = first;
    self->flags_28 = self->flags_28 | 1;
}
