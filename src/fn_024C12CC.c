#include "block.h"

/* 0x024C12CC .. 0x024C12D0, 2 instructions, 8 bytes.
   Stores +0x98. */

typedef struct { u8 pad0[0x98]; s32 field_98; } Obj;
void func_024C12CC(Obj *self, s32 value) { self->field_98 = value; }
