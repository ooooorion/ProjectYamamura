#include "block.h"

/* 0x023EF1D4 .. 0x023EF1D8, 2 instructions, 8 bytes.
   Stores +0x5F0. */

typedef struct { u8 pad0[0x5F0]; s32 value; } Obj;
void func_023EF1D4(Obj *self, s32 value) { self->value = value; }
