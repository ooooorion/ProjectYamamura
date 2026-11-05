#include "block.h"

/* 0x0245EF18 .. 0x0245EF1C, 2 instructions, 8 bytes.
   Stores +0x334. */

typedef struct { u8 pad0[0x334]; s32 field_334; } Obj;
void func_0245EF18(Obj *self, s32 value) { self->field_334 = value; }
