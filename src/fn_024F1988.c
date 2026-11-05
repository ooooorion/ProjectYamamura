#include "block.h"

/* 0x024F1988 .. 0x024F198C, 2 instructions, 8 bytes.
   Stores byte +0x325. */

typedef struct { u8 pad0[0x325]; s8 field_325; } Obj;
void func_024F1988(Obj *self, s8 value) { self->field_325 = value; }
