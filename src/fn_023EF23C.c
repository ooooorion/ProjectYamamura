#include "block.h"

/* 0x023EF23C .. 0x023EF240, 2 instructions, 8 bytes.
   Stores +0x624. */

typedef struct { u8 pad0[0x624]; s32 value; } Obj;
void func_023EF23C(Obj *self, s32 value) { self->value = value; }
