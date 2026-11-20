#include "block.h"

/* 0x024D8BB4 .. 0x024D8BBC, 2 instructions, 8 bytes.
   Stores byte +0x3E6. */

typedef struct { u8 pad0[0x3E6]; s8 field_3E6; } Obj;
void func_024D8BB4(Obj *self, s8 value) { self->field_3E6 = value; }
