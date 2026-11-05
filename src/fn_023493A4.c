#include "block.h"

/* 0x023493A4 .. 0x023493C4, 9 instructions, 36 bytes.
   True for states five and six. */

typedef struct { u8 pad0[0x34]; s32 field_34; } Obj;
s32 func_023493A4(Obj *self) {
    s32 value = self->field_34;
    if (value == 5 || value == 6) return 1;
    return 0;
}
