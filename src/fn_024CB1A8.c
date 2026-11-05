#include "block.h"

/* 0x024CB1A8 .. 0x024CB1AC, 2 instructions, 8 bytes.
   Stores +0x1310. */

typedef struct { u8 pad0[0x1310]; s32 field_1310; } Obj;
void func_024CB1A8(Obj *self, s32 value) { self->field_1310 = value; }
