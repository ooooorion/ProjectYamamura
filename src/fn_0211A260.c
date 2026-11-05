#include "block.h"

/* 0x0211A260 .. 0x0211A268, 3 instructions, 12 bytes.
   Sets the byte at +0x250. */

typedef struct {
    u8 pad0[0x250];
    u8 field_250;
} Obj;

void func_0211A260(Obj *self) {
    self->field_250 = 1;
}
