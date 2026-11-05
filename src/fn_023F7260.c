#include "block.h"

/* 0x023F7260 .. 0x023F7298, 15 instructions, 60 bytes.
   Returns the stored resource state or the default success value. */

typedef struct { u8 pad0[0x5FC]; s32 field_5FC; u8 pad600[0x90]; s32 field_690; } Obj;
extern s32 func_0241D3A8(s32 value);
s32 func_023F7260(Obj *self) {
    s32 result;
    result = 1;
    if (self->field_690 == 0) result = func_0241D3A8(self->field_5FC);
    return result;
}
