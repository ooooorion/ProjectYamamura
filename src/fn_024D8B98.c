#include "block.h"

/* 0x024D8B98 .. 0x024D8B9C, 2 instructions, 8 bytes.
   Stores byte +0x3EB. */

typedef struct { u8 pad0[0x3EB]; s8 field_3EB; } Obj;
void func_024D8B98(Obj *self, s8 value) { self->field_3EB = value; }
