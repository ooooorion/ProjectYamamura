#include "block.h"

/* 0x024D8A20 .. 0x024D8A24, 2 instructions, 8 bytes.
   Returns +0x3E0. */

typedef struct { u8 pad0[0x3E0]; s32 field_3E0; } Obj;
s32 func_024D8A20(Obj *self) { return self->field_3E0; }
