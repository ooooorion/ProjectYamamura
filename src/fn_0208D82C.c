#include "block.h"

/* 0x0208D82C .. 0x0208D844, 7 instructions, 28 bytes.
   Accumulates a float at +0xC8 and clamps it to the second argument; the
   comparison is `<` (blt), so equal values are left alone. */

typedef struct {
    u8 pad0[0xC8];
    f32 value_C8;
} Obj;

void func_0208D82C(Obj *self, f32 delta, f32 minimum) {
    f32 value;

    value = self->value_C8 + delta;
    if (value < minimum) {
        value = minimum;
    }
    self->value_C8 = value;
}
