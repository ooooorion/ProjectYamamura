#include "block.h"

/* 0x0245EDC8 .. 0x0245EDCC, 2 instructions, 8 bytes.
   Stores +0x328. */

typedef struct { u8 pad0[0x328]; s32 field_328; } Obj;
void func_0245EDC8(Obj *self, s32 value) { self->field_328 = value; }
