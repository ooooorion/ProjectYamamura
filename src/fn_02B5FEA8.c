#include "block.h"

/* 0x02B5FEA8 .. 0x02B5FEB0, 2 instructions, 8 bytes.
   Stores +0x11C. */

typedef struct { u8 pad0[0x11C]; s32 field_11C; } Obj;
void func_02B5FEA8(Obj *self, s32 value) { self->field_11C = value; }
