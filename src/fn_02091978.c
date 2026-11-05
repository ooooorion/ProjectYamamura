#include "block.h"

/* 0x02091978 .. 0x02091998, 9 instructions, 36 bytes.
   Subtracts +0x108 from +0xC8 and clamps the result to +0xD4 only when it is
   greater; equal values are left untouched. The local declaration order is
   load-bearing: declaring `limit` before `value` makes GHS keep the result in
   f0, as the target does. */

typedef struct {
    u8 pad0[0xC8];
    f32 value_C8;
    u8 pad_CC[8];
    f32 limit_D4;
    u8 pad_D8[0x30];
    f32 value_108;
} Obj;

void func_02091978(Obj *self) {
    f32 limit;
    f32 value;

    value = self->value_C8 - self->value_108;
    limit = self->limit_D4;
    if (value > limit) {
        value = limit;
    }
    self->value_C8 = value;
}
