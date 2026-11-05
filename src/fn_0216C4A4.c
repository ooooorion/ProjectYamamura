#include "block.h"

/* 0x0216C4A4 .. 0x0216C4CC, 11 instructions, 44 bytes.
   Returns 0 when the byte at +0x1F is set or when +0x120 - 10 is 0..2
   unsigned; otherwise 1. The subtract-before-compare is what makes the
   range check one cmplwi against 2. */

typedef struct {
    u8 pad0[0x1F];
    u8 flag_1F;
    u8 pad0_20[0x120 - 0x20];
    s32 field_120;
} Obj;

s32 func_0216C4A4(Obj *self) {
    if (self->flag_1F != 0 || (u32)(self->field_120 - 10) <= 2U) {
        return 0;
    }
    return 1;
}
