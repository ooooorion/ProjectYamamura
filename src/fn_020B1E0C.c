#include "block.h"

/* 0x020B1E0C .. 0x020B1E24, 7 instructions, 28 bytes.
   Clears +0x33C and +0x338, then replaces +0x334 with 1 - value, toggling
   between the two states. */

typedef struct {
    u8 pad0[0x334];
    s32 field_334;
    s32 field_338;
    s32 field_33C;
} Obj;

void func_020B1E0C(Obj *self) {
    self->field_33C = 0;
    self->field_338 = 0;
    self->field_334 = 1 - self->field_334;
}
