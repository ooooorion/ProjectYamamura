#include "block.h"

/* 0x023F4C2C .. 0x023F4C50, 10 instructions, 40 bytes.
   True when either active state field is set. */

typedef struct { u8 pad0[0x6EC]; s32 field_6EC; u8 field_6F0; } Obj;
s32 func_023F4C2C(Obj *self) {
    s32 result;
    result = 0;
    if (self->field_6F0 != 0 || self->field_6EC != -1) result = 1;
    return result;
}
