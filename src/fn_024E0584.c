#include "block.h"

/* 0x024E0584 .. 0x024E0588, 2 instructions, 8 bytes.
   Stores byte +0x34. */

typedef struct { u8 pad0[0x34]; s8 field_34; } Obj;
void func_024E0584(Obj *self, s8 value) { self->field_34 = value; }
