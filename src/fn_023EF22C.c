#include "block.h"

/* 0x023EF22C .. 0x023EF230, 2 instructions, 8 bytes.
   Stores +0x61C. */

typedef struct { u8 pad0[0x61C]; s32 value; } Obj;
void func_023EF22C(Obj *self, s32 value) { self->value = value; }
