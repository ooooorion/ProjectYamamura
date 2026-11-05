#include "block.h"

/* 0x021EF7FC .. 0x021EF800, 2 instructions, 8 bytes.
   Stores the argument at +0x18. */

typedef struct { u8 pad0[0x18]; s32 field_18; } Obj;
void func_021EF7FC(Obj *self, s32 value) { self->field_18 = value; }
