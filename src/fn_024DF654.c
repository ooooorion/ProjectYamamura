#include "block.h"

/* 0x024DF654 .. 0x024DF658, 2 instructions, 8 bytes.
   Stores +0x1C. */

typedef struct { u8 pad0[0x1C]; s32 field_1C; } Obj;
void func_024DF654(Obj *self, s32 value) { self->field_1C = value; }
