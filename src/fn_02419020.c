#include "block.h"

/* 0x02419020 .. 0x02419030, 5 instructions, 20 bytes.
   True unless +0x1E8 is 4. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_02419020(Obj *self) {
    return self->field_1E8 != 4;
}
