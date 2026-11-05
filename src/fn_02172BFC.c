#include "block.h"

/* 0x02172BFC .. 0x02172C2C, 13 instructions, 52 bytes.
   Post-increment a counter at +0x58 modulo 100 and return the old value.
   The divisor is the constant 100, so GHS emits the 0x51EB851F multiply
   sequence rather than a divide instruction. */

typedef struct {
    u8 pad0[0x58];
    s32 field_58;
} Obj;

s32 func_02172BFC(Obj *self) {
    s32 previous;

    previous = self->field_58;
    self->field_58 = (previous + 1) % 100;
    return previous;
}
