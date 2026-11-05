#include "block.h"

/* 0x020AE67C .. 0x020AE684, 3 instructions, 12 bytes.
   Sets the byte at +0x1D0 to 1. */

typedef struct {
    u8 pad0[0x1D0];
    u8 flag_1D0;
} Obj;

void func_020AE67C(Obj *self) {
    self->flag_1D0 = 1;
}
