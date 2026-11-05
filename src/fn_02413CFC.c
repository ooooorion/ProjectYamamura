#include "block.h"

/* 0x02413CFC .. 0x02413D0C, 5 instructions, 20 bytes.
   True unless +0x1E8 is 1. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_02413CFC(Obj *self) {
    return self->field_1E8 != 1;
}
