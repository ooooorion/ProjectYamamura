#include "block.h"

/* 0x02464770 .. 0x02464778, 2 instructions, 8 bytes.
   Stores +0xA74. */

typedef struct { u8 pad0[0xA74]; s32 field_A74; } Obj;
void func_02464770(Obj *self, s32 value) { self->field_A74 = value; }
