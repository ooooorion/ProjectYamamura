#include "block.h"

/* 0x023EF244 .. 0x023EF248, 2 instructions, 8 bytes.
   Stores +0x628. */

typedef struct { u8 pad0[0x628]; s32 value; } Obj;
void func_023EF244(Obj *self, s32 value) { self->value = value; }
