#include "block.h"

/* 0x024DCF48 .. 0x024DCF4C, 2 instructions, 8 bytes.
   Stores byte +0x112. */

typedef struct { u8 pad0[0x112]; s8 field_112; } Obj;
void func_024DCF48(Obj *self, s8 value) { self->field_112 = value; }
