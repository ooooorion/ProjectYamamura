#include "block.h"

/* 0x023EF1FC .. 0x023EF200, 2 instructions, 8 bytes.
   Stores +0x604. */

typedef struct { u8 pad0[0x604]; s32 value; } Obj;
void func_023EF1FC(Obj *self, s32 value) { self->value = value; }
