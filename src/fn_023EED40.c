#include "block.h"

/* 0x023EED40 .. 0x023EED50, 5 instructions, 20 bytes.
   True when +0x6C4 is two. */

typedef struct { u8 pad0[0x6C4]; s32 field_6C4; } Obj;
s32 func_023EED40(Obj *self) { return (self->field_6C4 ^ 2) == 0; }
