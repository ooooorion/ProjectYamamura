#include "block.h"

/* 0x024F0724 .. 0x024F072C, 3 instructions, 12 bytes.
   Sets byte +0x22A. */

typedef struct { u8 pad0[0x22A]; s8 field_22A; } Obj;
void func_024F0724(Obj *self) { self->field_22A = 1; }
