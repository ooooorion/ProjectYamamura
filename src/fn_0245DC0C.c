#include "block.h"

/* 0x0245DC0C .. 0x0245DC18, 4 instructions, 16 bytes.
   Clears the low active flag at +0x118. */

typedef struct { u8 pad0[0x118]; s32 field_118; } Obj;
void func_0245DC0C(Obj *self) { self->field_118 = self->field_118 & 0xFFFFFFFE; }
