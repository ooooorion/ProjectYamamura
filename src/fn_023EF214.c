#include "block.h"

/* 0x023EF214 .. 0x023EF218, 2 instructions, 8 bytes.
   Stores +0x610. */

typedef struct { u8 pad0[0x610]; s32 value; } Obj;
void func_023EF214(Obj *self, s32 value) { self->value = value; }
