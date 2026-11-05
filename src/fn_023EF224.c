#include "block.h"

/* 0x023EF224 .. 0x023EF228, 2 instructions, 8 bytes.
   Stores +0x618. */

typedef struct { u8 pad0[0x618]; s32 value; } Obj;
void func_023EF224(Obj *self, s32 value) { self->value = value; }
