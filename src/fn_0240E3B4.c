#include "block.h"

/* 0x0240E3B4 .. 0x0240E3C4, 5 instructions, 20 bytes.
   Returns true when the type field is not 0xC. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_0240E3B4(Obj *self) {
    return self->field_1E8 != 0xC;
}
