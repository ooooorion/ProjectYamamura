#include "block.h"

/* 0x022F3274 .. 0x022F327C, 3 instructions, 12 bytes.
   Stores through the +4 pointer at +0xCF0. */

typedef struct { u8 pad0[0xCF0]; s32 field_CF0; } Sub;
typedef struct { u8 pad0[4]; Sub *field_4; } Obj;
void func_022F3274(Obj *self, s32 arg1) { self->field_4->field_CF0 = arg1; }
