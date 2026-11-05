#include "block.h"

/* 0x024C1284 .. 0x024C1288, 2 instructions, 8 bytes.
   Stores +0xA0. */

typedef struct { u8 pad0[0xA0]; s32 field_A0; } Obj;
void func_024C1284(Obj *self, s32 value) { self->field_A0 = value; }
