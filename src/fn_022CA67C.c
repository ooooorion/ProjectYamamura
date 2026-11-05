#include "block.h"

/* 0x022CA67C .. 0x022CA680, 2 instructions, 8 bytes.
   Stores the argument at +0x44. */

typedef struct { u8 pad0[0x44]; s32 field_44; } Obj;
void func_022CA67C(Obj *self, s32 arg1) { self->field_44 = arg1; }
