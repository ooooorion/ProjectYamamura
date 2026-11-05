#include "block.h"

/* 0x024DF74C .. 0x024DF750, 2 instructions, 8 bytes.
   Stores byte +0x30. */

typedef struct { u8 pad0[0x30]; s8 field_30; } Obj;
void func_024DF74C(Obj *self, s8 value) { self->field_30 = value; }
