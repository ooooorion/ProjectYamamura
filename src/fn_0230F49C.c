#include "block.h"

/* 0x0230F49C .. 0x0230F4A8, 4 instructions, 16 bytes.
   Copies a float constant to +0x328. */

typedef struct { u8 pad0[0x328]; f32 field_328; } Obj;
void func_0230F49C(Obj *self) { self->field_328 = *(f32 *)0x10063238; }
