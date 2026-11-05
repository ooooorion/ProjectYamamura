#include "block.h"

/* 0x0209EE44 .. 0x0209EE4C, 3 instructions, 12 bytes.
   Sets the byte at +0x1F to 1. */

typedef struct {
    u8 pad0[0x1F];
    u8 flag_1F;
} Obj;

void func_0209EE44(Obj *self) {
    self->flag_1F = 1;
}
