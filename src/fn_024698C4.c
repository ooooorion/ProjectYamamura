#include "block.h"

/* 0x024698C4 .. 0x024698C8, 2 instructions, 8 bytes.
   Stores +0x2B0. */

typedef struct { u8 pad0[0x2B0]; s32 field_2B0; } Obj;
void func_024698C4(Obj *self, s32 value) { self->field_2B0 = value; }
