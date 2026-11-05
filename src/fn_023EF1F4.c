#include "block.h"

/* 0x023EF1F4 .. 0x023EF1F8, 2 instructions, 8 bytes.
   Stores +0x600. */

typedef struct { u8 pad0[0x600]; s32 value; } Obj;
void func_023EF1F4(Obj *self, s32 value) { self->value = value; }
