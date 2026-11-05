#include "block.h"

/* 0x023EF1DC .. 0x023EF1E0, 2 instructions, 8 bytes.
   Stores +0x5F4. */

typedef struct { u8 pad0[0x5F4]; s32 value; } Obj;
void func_023EF1DC(Obj *self, s32 value) { self->value = value; }
