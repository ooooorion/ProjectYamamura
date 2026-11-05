#include "block.h"

/* 0x024750EC .. 0x024750F0, 2 instructions, 8 bytes.
   Stores +0x230. */

typedef struct { u8 pad0[0x230]; s32 field_230; } Obj;
void func_024750EC(Obj *self, s32 value) { self->field_230 = value; }
