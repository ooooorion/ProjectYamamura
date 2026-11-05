#include "block.h"

/* 0x024C129C .. 0x024C12A0, 2 instructions, 8 bytes.
   Stores +0x84. */

typedef struct { u8 pad0[0x84]; s32 field_84; } Obj;
void func_024C129C(Obj *self, s32 value) { self->field_84 = value; }
