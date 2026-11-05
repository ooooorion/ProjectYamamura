#include "block.h"

/* 0x020163DC .. 0x020163F0, 6 instructions, 24 bytes.
   Two pointers at +0x220 and +0x224, each leading to a byte at +0x100.
   Reusing one local pointer keeps both loads in r12 and the zero in r11,
   exactly as the target does; spelling the two dereferences inline instead
   loads the second pointer early and lands in r10/r12 at -O2. */

typedef struct {
    u8 pad0[256];
    u8 flag_256;
} Child;

typedef struct {
    u8 pad0[544];
    Child *child_544;
    Child *child_548;
} Obj;

void func_020163DC(Obj *self) {
    Child *child = self->child_544;
    child->flag_256 = 0;
    child = self->child_548;
    child->flag_256 = 0;
}
