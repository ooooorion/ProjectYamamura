#include "block.h"

/* 0x024698CC .. 0x024698D4, 2 instructions, 8 bytes.
   Stores +0x2A0. */

typedef struct { u8 pad0[0x2A0]; s32 field_2A0; } Obj;
void func_024698CC(Obj *self, s32 value) { self->field_2A0 = value; }
