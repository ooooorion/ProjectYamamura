#include "block.h"

/* 0x0247DF04 .. 0x0247DF14, 5 instructions, 20 bytes.
   True when +0x14C8 is 0x10. */

typedef struct { u8 pad0[0x14C8]; s32 field_14C8; } Obj;
s32 func_0247DF04(Obj *self) { return (self->field_14C8 ^ 0x10) == 0; }
