#include "block.h"

/* 0x023EF21C .. 0x023EF220, 2 instructions, 8 bytes.
   Stores +0x614. */

typedef struct { u8 pad0[0x614]; s32 value; } Obj;
void func_023EF21C(Obj *self, s32 value) { self->value = value; }
