#include "block.h"

/* 0x020A35CC .. 0x020A35EC, 9 instructions, 36 bytes.
   Returns 0 only for a non-null object whose bit 14 at +0x60 is set; the
   null test and the bit test share the same failure path. */

typedef struct {
    u8 pad0[0x60];
    u32 bits_60;
} Obj;

s32 func_020A35CC(Obj *self) {
    if (self != 0 && ((self->bits_60 >> 14) & 1)) {
        return 0;
    }
    return 1;
}
