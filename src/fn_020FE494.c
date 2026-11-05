#include "block.h"

/* 0x020FE494 .. 0x020FE4AC, 7 instructions, 28 bytes.
   Sum of the child's +0xBC and the two object floats at +0x8C/+0x94. */

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

f32 func_020FE494(Obj *self) {
    return self->child_38->value_BC + self->value_8C + self->value_94;
}
