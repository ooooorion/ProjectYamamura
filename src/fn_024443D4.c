#include "block.h"

/* 0x024443D4 .. 0x024443DC, 3 instructions, 12 bytes.
   Clears byte +0x2B0. */

typedef struct { u8 pad0[0x2B0]; s8 field_2B0; } Obj;
void func_024443D4(Obj *self) { self->field_2B0 = 0; }
