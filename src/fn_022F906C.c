#include "block.h"

/* 0x022F906C .. 0x022F9070, 2 instructions, 8 bytes.
   Stores the argument at +0x54. */

typedef struct { u8 pad0[0x54]; s32 field_54; } Obj;
void func_022F906C(Obj *self, s32 arg1) { self->field_54 = arg1; }
