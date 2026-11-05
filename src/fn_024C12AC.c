#include "block.h"

/* 0x024C12AC .. 0x024C12B0, 2 instructions, 8 bytes.
   Stores +0x7C. */

typedef struct { u8 pad0[0x7C]; s32 field_7C; } Obj;
void func_024C12AC(Obj *self, s32 value) { self->field_7C = value; }
