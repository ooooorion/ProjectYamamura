#include "block.h"

/* 0x023B975C .. 0x023B976C, 5 instructions, 20 bytes.
   True when +0x1E8 is four. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_023B975C(Obj *self) { return (self->field_1E8 ^ 4) == 0; }
