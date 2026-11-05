#include "block.h"

/* 0x024563B4 .. 0x024563B8, 2 instructions, 8 bytes.
   Stores +0x1C2C. */

typedef struct { u8 pad0[0x1C2C]; s32 field_1C2C; } Obj;
void func_024563B4(Obj *self, s32 value) { self->field_1C2C = value; }
