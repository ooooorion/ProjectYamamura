#include "block.h"

/* 0x024C1294 .. 0x024C1298, 2 instructions, 8 bytes.
   Stores +0xA8. */

typedef struct { u8 pad0[0xA8]; s32 field_A8; } Obj;
void func_024C1294(Obj *self, s32 value) { self->field_A8 = value; }
