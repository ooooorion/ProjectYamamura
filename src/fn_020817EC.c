#include "block.h"

/* 0x020817EC .. 0x020817F8, 4 instructions, 16 bytes.
   Copies the float constant at 0x1000CF8C into +0x10. */

typedef struct {
    u8 pad0[0x10];
    f32 value_10;
} Obj;

void func_020817EC(Obj *self) {
    self->value_10 = *(f32 *)0x1000CF8C;
}
