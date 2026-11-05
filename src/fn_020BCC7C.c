#include "block.h"

/* 0x020BCC7C .. 0x020BCC84, 3 instructions, 12 bytes.
   Clears the byte at +0x1C8. */

typedef struct {
    u8 pad0[0x1C8];
    u8 flag_1C8;
} Obj;

void func_020BCC7C(Obj *self) {
    self->flag_1C8 = 0;
}
