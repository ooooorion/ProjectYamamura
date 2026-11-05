#include "block.h"

/* 0x023EF20C .. 0x023EF210, 2 instructions, 8 bytes.
   Stores +0x60C. */

typedef struct { u8 pad0[0x60C]; s32 value; } Obj;
void func_023EF20C(Obj *self, s32 value) { self->value = value; }
