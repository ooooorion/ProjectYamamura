#include "block.h"

/* 0x024D8A28 .. 0x024D8A2C, 2 instructions, 8 bytes.
   Stores +0x3E0. */

typedef struct { u8 pad0[0x3E0]; s32 field_3E0; } Obj;
void func_024D8A28(Obj *self, s32 value) { self->field_3E0 = value; }
