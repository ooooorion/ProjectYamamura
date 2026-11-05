#include "block.h"

/* 0x02401474 .. 0x02401480, 4 instructions, 16 bytes.
   Returns true when the type field is zero. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_02401474(Obj *self) {
    return self->field_1E8 == 0;
}
