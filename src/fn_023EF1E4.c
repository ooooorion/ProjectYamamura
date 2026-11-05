#include "block.h"

/* 0x023EF1E4 .. 0x023EF1E8, 2 instructions, 8 bytes.
   Stores +0x5F8. */

typedef struct { u8 pad0[0x5F8]; s32 value; } Obj;
void func_023EF1E4(Obj *self, s32 value) { self->value = value; }
