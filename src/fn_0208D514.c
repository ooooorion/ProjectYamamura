#include "block.h"

/* 0x0208D514 .. 0x0208D538, 10 instructions, 40 bytes.
   Reads the child pointer at +0x34C and accepts it when its state word at
   +0x08 is 2. Both the null test and the state test feed the 1/0 result. */

typedef struct {
    u8 pad0[0x34C];
    void *child_34C;
} Obj;

typedef struct {
    u8 pad0[8];
    s32 state_08;
} Child;

s32 func_0208D514(Obj *self) {
    void *child;

    child = self->child_34C;
    if (child != 0 && ((Child *)child)->state_08 == 2) {
        return 1;
    }
    return 0;
}
