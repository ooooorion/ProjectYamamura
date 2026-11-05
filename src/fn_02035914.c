#include "block.h"

/* 0x02035914 .. 0x02035938, 10 instructions, 40 bytes.
   Clear byte +0x100 on the child at +0x58, then on the child at +0x50.
   The void-pointer/byte-cast form keeps GHS from hoisting the zero store
   above the null test; a typed Child * instead produces li r0,0 before cmpwi.
   The +0x54 pointer-sized field is intentionally skipped by pad_54. */

typedef struct {
    u8 pad0[0x50];
    void *child_50;
    u8 pad_54[4];
    void *child_58;
} Obj;

void func_02035914(Obj *self) {
    void *child_58;
    void *child_50;

    child_58 = self->child_58;
    if (child_58 != 0) *((u8 *)child_58 + 0x100) = 0;

    child_50 = self->child_50;
    if (child_50 != 0) *((u8 *)child_50 + 0x100) = 0;
}
