#include "block.h"

/* 0x024E0574 .. 0x024E0578, 2 instructions, 8 bytes.
   Stores byte +0x33. */

typedef struct { u8 pad0[0x33]; s8 field_33; } Obj;
void func_024E0574(Obj *self, s8 value) { self->field_33 = value; }
