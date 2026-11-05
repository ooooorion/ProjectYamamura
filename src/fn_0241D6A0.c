#include "block.h"

/* 0x0241D6A0 .. 0x0241D6B0, 5 instructions, 20 bytes.
   True unless +0x1E8 is 2. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_0241D6A0(Obj *self) {
    return self->field_1E8 != 2;
}
