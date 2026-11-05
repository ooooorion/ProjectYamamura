#include "block.h"

/* 0x0241D338 .. 0x0241D348, 5 instructions, 20 bytes.
   True unless +0x1E8 is 5. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_0241D338(Obj *self) {
    return self->field_1E8 != 5;
}
