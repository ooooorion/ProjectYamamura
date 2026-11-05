#include "block.h"

/* 0x024DF300 .. 0x024DF304, 2 instructions, 8 bytes.
   Stores +0x18. */

typedef struct { u8 pad0[0x18]; s32 field_18; } Obj;
void func_024DF300(Obj *self, s32 value) { self->field_18 = value; }
