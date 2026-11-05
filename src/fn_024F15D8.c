#include "block.h"

/* 0x024F15D8 .. 0x024F15DC, 2 instructions, 8 bytes.
   Stores byte +0x324. */

typedef struct { u8 pad0[0x324]; s8 field_324; } Obj;
void func_024F15D8(Obj *self, s8 value) { self->field_324 = value; }
