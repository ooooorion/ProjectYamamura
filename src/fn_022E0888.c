#include "block.h"

/* 0x022E0888 .. 0x022E0890, 3 instructions, 12 bytes.
   Stores one at +8. */

typedef struct { u8 pad0[8]; s32 field_8; } Obj;
void func_022E0888(Obj *self) { self->field_8 = 1; }
