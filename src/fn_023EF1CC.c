#include "block.h"

/* 0x023EF1CC .. 0x023EF1D0, 2 instructions, 8 bytes.
   Stores +0x5EC. */

typedef struct { u8 pad0[0x5EC]; s32 value; } Obj;
void func_023EF1CC(Obj *self, s32 value) { self->value = value; }
