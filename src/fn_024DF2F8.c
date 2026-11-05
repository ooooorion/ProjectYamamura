#include "block.h"

/* 0x024DF2F8 .. 0x024DF2FC, 2 instructions, 8 bytes.
   Stores +0x10. */

typedef struct { u8 pad0[0x10]; s32 field_10; } Obj;
void func_024DF2F8(Obj *self, s32 value) { self->field_10 = value; }
