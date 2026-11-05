#include "block.h"

/* 0x02035954 .. 0x0203595C, 3 instructions, 12 bytes.
   li/stb/blr: set the byte at +0xCD. */

typedef struct {
    u8 pad0[0xCD];
    u8 flag_CD;
} Obj;

void func_02035954(Obj *self) {
    self->flag_CD = 1;
}
