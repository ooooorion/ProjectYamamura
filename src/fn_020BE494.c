#include "block.h"

/* 0x020BE494 .. 0x020BE49C, 3 instructions, 12 bytes.
   Stores the argument at +0x18 of the child pointer held at +0x20;
   see 0x020BE464. */

typedef struct {
    u8 pad0[0x20];
    void *child_20;
} Obj;

typedef struct {
    u8 pad0[0x18];
    s32 field_18;
} Child;

void func_020BE494(Obj *self, s32 value) {
    ((Child *)self->child_20)->field_18 = value;
}
