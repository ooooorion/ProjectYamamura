#include "block.h"

/* 0x02973640 .. 0x02973648, 2 instructions, 8 bytes.
   Stores byte +3. */

typedef struct { u8 pad0[3]; s8 field_3; } Obj;
void func_02973640(Obj *self, s8 value) { self->field_3 = value; }
