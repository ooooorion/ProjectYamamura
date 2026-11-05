#include "block.h"

/* 0x023EF24C .. 0x023EF250, 2 instructions, 8 bytes.
   Stores +0x62C. */

typedef struct { u8 pad0[0x62C]; s32 value; } Obj;
void func_023EF24C(Obj *self, s32 value) { self->value = value; }
