#include "block.h"

/* 0x023EF1EC .. 0x023EF1F0, 2 instructions, 8 bytes.
   Stores +0x5FC. */

typedef struct { u8 pad0[0x5FC]; s32 value; } Obj;
void func_023EF1EC(Obj *self, s32 value) { self->value = value; }
