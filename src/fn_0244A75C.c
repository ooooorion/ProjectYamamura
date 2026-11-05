#include "block.h"

/* 0x0244A75C .. 0x0244A764, 3 instructions, 12 bytes.
   Returns +0x93C offset by 0xC8. */

typedef struct { u8 pad0[0x93C]; s32 field_93C; } Obj;
s32 func_0244A75C(Obj *self) { return self->field_93C + 0xC8; }
