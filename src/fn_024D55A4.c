#include "block.h"

/* 0x024D55A4 .. 0x024D55A8, 2 instructions, 8 bytes.
   Returns +0x1E0. */

typedef struct { u8 pad0[0x1E0]; s32 field_1E0; } Obj;
s32 func_024D55A4(Obj *self) { return self->field_1E0; }
