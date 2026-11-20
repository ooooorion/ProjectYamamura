#include "block.h"

/* 0x02A4D920 .. 0x02A4D928, 2 instructions, 8 bytes.
   Stores +0x28. */

typedef struct { u8 pad0[0x28]; s32 field_28; } Obj;
void func_02A4D920(Obj *self, s32 value) { self->field_28 = value; }
