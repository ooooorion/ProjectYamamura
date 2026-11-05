#include "block.h"

/* 0x020818B0 .. 0x020818B4, 2 instructions, 8 bytes.
   Float getter for +0x10; pairs with 0x020817EC. */

typedef struct {
    u8 pad0[0x10];
    f32 value_10;
} Obj;

f32 func_020818B0(Obj *self) {
    return self->value_10;
}
