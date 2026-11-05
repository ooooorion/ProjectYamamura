#include "block.h"

/* 0x0245FDDC .. 0x0245FDE0, 2 instructions, 8 bytes.
   Stores byte +0x354. */

typedef struct { u8 pad0[0x354]; s8 field_354; } Obj;
void func_0245FDDC(Obj *self, s8 value) { self->field_354 = value; }
