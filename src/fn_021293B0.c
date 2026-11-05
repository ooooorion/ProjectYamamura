#include "block.h"

/* 0x021293B0 .. 0x021293B8, 3 instructions, 12 bytes.
   Clears the word at +0x2F4. */

typedef struct {
    u8 pad0[0x2F4];
    s32 field_2F4;
} Obj;

void func_021293B0(Obj *self) {
    self->field_2F4 = 0;
}
