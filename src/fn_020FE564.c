#include "block.h"

/* 0x020FE564 .. 0x020FE574, 5 instructions, 20 bytes.
   Child +0x30C plus the object float at +0x8C. */

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

f32 func_020FE564(Obj *self) {
    return self->child_38->value_30C + self->value_8C;
}
