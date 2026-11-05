#include "block.h"

/* 0x024EE98C .. 0x024EE990, 2 instructions, 8 bytes.
   Stores byte +0x323. */

typedef struct { u8 pad0[0x323]; s8 field_323; } Obj;
void func_024EE98C(Obj *self, s8 value) { self->field_323 = value; }
