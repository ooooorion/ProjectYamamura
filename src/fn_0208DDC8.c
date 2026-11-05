#include "block.h"

/* 0x0208DDC8 .. 0x0208DDD0, 3 instructions, 12 bytes.
   Clears the word at +0x2F8. */

typedef struct {
    u8 pad0[0x2F8];
    s32 field_2F8;
} Obj;

void func_0208DDC8(Obj *self) {
    self->field_2F8 = 0;
}
