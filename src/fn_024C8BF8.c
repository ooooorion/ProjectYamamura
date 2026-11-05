#include "block.h"

/* 0x024C8BF8 .. 0x024C8BFC, 2 instructions, 8 bytes.
   Stores +0x78. */

typedef struct { u8 pad0[0x78]; s32 field_78; } Obj;
void func_024C8BF8(Obj *self, s32 value) { self->field_78 = value; }
