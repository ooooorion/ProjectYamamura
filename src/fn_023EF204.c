#include "block.h"

/* 0x023EF204 .. 0x023EF208, 2 instructions, 8 bytes.
   Stores +0x608. */

typedef struct { u8 pad0[0x608]; s32 value; } Obj;
void func_023EF204(Obj *self, s32 value) { self->value = value; }
