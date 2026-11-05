#include "block.h"

/* 0x024C2358 .. 0x024C2378, 9 instructions, 36 bytes.
   True for type states two and three. */

typedef struct { u8 pad0[0xC]; s32 field_C; } Obj;
s32 func_024C2358(Obj *self) {
    s32 state;

    state = self->field_C;
    if (state == 2 || state == 3) return 1;
    return 0;
}
