#include "block.h"

/* 0x023EF1C4 .. 0x023EF1C8, 2 instructions, 8 bytes.
   Stores +0x5E8. */

typedef struct { u8 pad0[0x5E8]; s32 value; } Obj;
void func_023EF1C4(Obj *self, s32 value) { self->value = value; }
