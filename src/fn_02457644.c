#include "block.h"

/* 0x02457644 .. 0x02457648, 2 instructions, 8 bytes.
   Stores byte +0x1C4D. */

typedef struct { u8 pad0[0x1C4D]; s8 field_1C4D; } Obj;
void func_02457644(Obj *self, s8 value) { self->field_1C4D = value; }
