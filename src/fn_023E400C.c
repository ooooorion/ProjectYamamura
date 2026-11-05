#include "block.h"

/* 0x023E400C .. 0x023E401C, 5 instructions, 20 bytes.
   True when +0x18 is two. */

typedef struct { u8 pad0[0x18]; s32 field_18; } Obj;
s32 func_023E400C(Obj *self) { return (self->field_18 ^ 2) == 0; }
