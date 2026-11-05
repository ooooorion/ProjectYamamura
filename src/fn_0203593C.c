#include "block.h"

/* 0x0203593C .. 0x02035950, 6 instructions, 24 bytes.
   Set byte +0x100 on the child at +0x50. */

typedef struct {
    u8 pad0[0x100];
    u8 flag_100;
} Child;

typedef struct {
    u8 pad0[0x50];
    Child *child_50;
} Obj;

void func_0203593C(Obj *self) {
    Child *child;

    child = self->child_50;
    if (child != 0) child->flag_100 = 1;
}
