#include "block.h"

/* 0x02456270 .. 0x02456274, 2 instructions, 8 bytes.
   Stores +0x1C20. */

typedef struct { u8 pad0[0x1C20]; s32 field_1C20; } Obj;
void func_02456270(Obj *self, s32 value) { self->field_1C20 = value; }
