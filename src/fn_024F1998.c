#include "block.h"

/* 0x024F1998 .. 0x024F199C, 2 instructions, 8 bytes.
   Stores +0x240. */

typedef struct { u8 pad0[0x240]; s32 field_240; } Obj;
void func_024F1998(Obj *self, s32 value) { self->field_240 = value; }
