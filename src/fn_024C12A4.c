#include "block.h"

/* 0x024C12A4 .. 0x024C12A8, 2 instructions, 8 bytes.
   Stores +0x88. */

typedef struct { u8 pad0[0x88]; s32 field_88; } Obj;
void func_024C12A4(Obj *self, s32 value) { self->field_88 = value; }
