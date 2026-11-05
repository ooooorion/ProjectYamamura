#include "block.h"

/* 0x024D8B60 .. 0x024D8B64, 2 instructions, 8 bytes.
   Returns +0x1F4. */

typedef struct { u8 pad0[0x1F4]; s32 field_1F4; } Obj;
s32 func_024D8B60(Obj *self) { return self->field_1F4; }
