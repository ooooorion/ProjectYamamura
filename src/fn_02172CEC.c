#include "block.h"

/* 0x02172CEC .. 0x02172D1C, 13 instructions, 52 bytes.
   True only when the child at +0x50 exists and both bytes +0x14 and +0x15
   are non-zero. The child is loaded once and reused for both byte tests. */

typedef struct {
    u8 pad0[0x14];
    u8 flag_14;
    u8 flag_15;
} Child;

typedef struct {
    u8 pad0[0x50];
    Child *child_50;
} Obj;

s32 func_02172CEC(Obj *self) {
    Child *child;

    child = self->child_50;
    if (child != 0 && child->flag_14 != 0 && child->flag_15 != 0) {
        return 1;
    }
    return 0;
}
