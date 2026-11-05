#include "block.h"

/* 0x024D51EC .. 0x024D51F0, 2 instructions, 8 bytes.
   Returns +0x1E0. */

typedef struct { u8 pad0[0x1E0]; s32 field_1E0; } Obj;
s32 func_024D51EC(Obj *self) { return self->field_1E0; }
