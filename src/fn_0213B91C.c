#include "block.h"

/* 0x0213B91C .. 0x0213B930, 6 instructions, 24 bytes.
   Publishes a word at +0x1C and, when the child exists, at child +0x54. */

typedef struct {
    u8 pad0[0x54];
    s32 field_54;
} Child;

typedef struct {
    u8 pad0[0x1C];
    s32 field_1C;
    u8 pad0_20[0x84 - 0x20];
    Child *child_84;
} Obj;

void func_0213B91C(Obj *self, s32 value) {
    Child *child;

    child = self->child_84;
    if (child != 0) {
        child->field_54 = value;
    }
    self->field_1C = value;
}
