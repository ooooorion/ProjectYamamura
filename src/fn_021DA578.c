#include "block.h"

/* 0x021DA578 .. 0x021DA59C, 10 instructions, 40 bytes.
   Rejects state 3 unless +0x5F8 is also 2. */

typedef struct { u8 pad0[0x4F4]; s32 field_4F4; u8 pad4F8[0x100]; s32 field_5F8; } Obj;
s32 func_021DA578(Obj *self) {
    if (self->field_4F4 == 3 && self->field_5F8 != 2) return 0;
    return 1;
}
