#include "block.h"

/* 0x0213AADC .. 0x0213AAE4, 3 instructions, 12 bytes.
   Writes a byte through the child pointer at +0x84. */

typedef struct {
    u8 pad0[0x6D];
    s8 field_6D;
} Child;

typedef struct {
    u8 pad0[0x84];
    Child *child_84;
} Obj;

void func_0213AADC(Obj *self, s8 value) {
    self->child_84->field_6D = value;
}
