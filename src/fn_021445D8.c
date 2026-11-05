#include "block.h"

/* 0x021445D8 .. 0x021445FC, 10 instructions, 40 bytes.
   State test: +0x308 must be 1 and the byte at +0x526 non-zero. */

typedef struct {
    u8 pad0[0x308];
    s32 field_308;
    u8 pad0_30C[0x526 - 0x30C];
    u8 flag_526;
} Obj;

s32 func_021445D8(Obj *self) {
    if (self->field_308 == 1 && self->flag_526 != 0) {
        return 1;
    }
    return 0;
}
