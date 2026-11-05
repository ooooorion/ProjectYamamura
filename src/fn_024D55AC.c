#include "block.h"

/* 0x024D55AC .. 0x024D55B0, 2 instructions, 8 bytes.
   Returns +0x1F0. */

typedef struct { u8 pad0[0x1F0]; s32 field_1F0; } Obj;
s32 func_024D55AC(Obj *self) { return self->field_1F0; }
