#include "block.h"

/* 0x020AE688 .. 0x020AE690, 3 instructions, 12 bytes.
   Loads the pointer at +0x1DC and returns the word it points to. */

typedef struct {
    u8 pad0[0x1DC];
    s32 *pointer_1DC;
} Obj;

s32 func_020AE688(Obj *self) {
    return *self->pointer_1DC;
}
