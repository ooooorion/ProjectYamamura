#include "block.h"

/* 0x0245DBFC .. 0x0245DC08, 4 instructions, 16 bytes.
   Sets the low active flag at +0x118. */

typedef struct { u8 pad0[0x118]; s32 field_118; } Obj;
void func_0245DBFC(Obj *self) { self->field_118 = self->field_118 | 1; }
