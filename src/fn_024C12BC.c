#include "block.h"

/* 0x024C12BC .. 0x024C12C0, 2 instructions, 8 bytes.
   Stores +0x94. */

typedef struct { u8 pad0[0x94]; s32 field_94; } Obj;
void func_024C12BC(Obj *self, s32 value) { self->field_94 = value; }
