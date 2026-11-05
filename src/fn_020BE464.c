#include "block.h"

/* 0x020BE464 .. 0x020BE46C, 3 instructions, 12 bytes.
   Stores the argument at +0x14 of the child pointer held at +0x20;
   0x020BE494 writes +0x18 of the same child. */

typedef struct {
    u8 pad0[0x20];
    void *child_20;
} Obj;

typedef struct {
    u8 pad0[0x14];
    s32 field_14;
} Child;

void func_020BE464(Obj *self, s32 value) {
    ((Child *)self->child_20)->field_14 = value;
}
