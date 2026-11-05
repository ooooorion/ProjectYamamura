#include "block.h"

/* 0x024F19A0 .. 0x024F19A4, 2 instructions, 8 bytes.
   Returns +0x240. */

typedef struct { u8 pad0[0x240]; s32 field_240; } Obj;
s32 func_024F19A0(Obj *self) { return self->field_240; }
