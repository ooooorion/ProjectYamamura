#include "block.h"

/* 0x023EED2C .. 0x023EED3C, 5 instructions, 20 bytes.
   True when +0x6C4 is one. */

typedef struct { u8 pad0[0x6C4]; s32 field_6C4; } Obj;
s32 func_023EED2C(Obj *self) { return (self->field_6C4 ^ 1) == 0; }
