#include "block.h"

/* 0x0247A134 .. 0x0247A140, 4 instructions, 16 bytes.
   Sets the low active flag at +0x118. */

typedef struct { u8 pad0[0x118]; s32 field_118; } Obj;
void func_0247A134(Obj *self) { self->field_118 = self->field_118 | 1; }
