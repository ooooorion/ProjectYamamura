#include "block.h"

/* 0x024C12C4 .. 0x024C12C8, 2 instructions, 8 bytes.
   Stores +0x9C. */

typedef struct { u8 pad0[0x9C]; s32 field_9C; } Obj;
void func_024C12C4(Obj *self, s32 value) { self->field_9C = value; }
