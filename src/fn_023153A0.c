#include "block.h"

/* 0x023153A0 .. 0x023153A4, 2 instructions, 8 bytes.
   Stores the argument at +0xD6C. */

typedef struct { u8 pad0[0xD6C]; s32 field_D6C; } Obj;
void func_023153A0(Obj *self, s32 arg1) { self->field_D6C = arg1; }
