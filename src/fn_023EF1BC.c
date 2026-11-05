#include "block.h"

/* 0x023EF1BC .. 0x023EF1C0, 2 instructions, 8 bytes.
   Stores +0x5E4. */

typedef struct { u8 pad0[0x5E4]; s32 value; } Obj;
void func_023EF1BC(Obj *self, s32 value) { self->value = value; }
