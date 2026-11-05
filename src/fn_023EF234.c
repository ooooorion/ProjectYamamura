#include "block.h"

/* 0x023EF234 .. 0x023EF238, 2 instructions, 8 bytes.
   Stores +0x620. */

typedef struct { u8 pad0[0x620]; s32 value; } Obj;
void func_023EF234(Obj *self, s32 value) { self->value = value; }
