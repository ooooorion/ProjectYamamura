#include "block.h"

/* 0x020FE4E0 .. 0x020FE4F8, 7 instructions, 28 bytes.
   Same sum one slot lower, at +0xB8/+0x88/+0x90. */

typedef struct {
    u8 pad0[0xB8];
    f32 value_B8;
    f32 value_BC;
    u8 pad0_C0[0x30C - 0xC0];
    f32 value_30C;
} Child;

typedef struct {
    u8 pad0[0x38];
    Child *child_38;
    u8 pad0_3C[0x88 - 0x3C];
    f32 value_88;
    f32 value_8C;
    f32 value_90;
    f32 value_94;
} Obj;

f32 func_020FE4E0(Obj *self) {
    return self->child_38->value_B8 + self->value_88 + self->value_90;
}
