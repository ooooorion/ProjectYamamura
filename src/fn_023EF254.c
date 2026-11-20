#include "block.h"

/* 0x023EF254 .. 0x023EF25C, 2 instructions, 8 bytes.
   Stores +0x630. */

typedef struct { u8 pad0[0x630]; s32 value; } Obj;
void func_023EF254(Obj *self, s32 value) { self->value = value; }
