#include "block.h"

/* 0x024C12B4 .. 0x024C12B8, 2 instructions, 8 bytes.
   Stores +0x80. */

typedef struct { u8 pad0[0x80]; s32 field_80; } Obj;
void func_024C12B4(Obj *self, s32 value) { self->field_80 = value; }
