#include "block.h"

/* 0x024EBA40 .. 0x024EBA44, 2 instructions, 8 bytes.
   Stores +0xD0. */

typedef struct { u8 pad0[0xD0]; s32 field_D0; } Obj;
void func_024EBA40(Obj *self, s32 value) { self->field_D0 = value; }
