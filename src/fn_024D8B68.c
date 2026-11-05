#include "block.h"

/* 0x024D8B68 .. 0x024D8B6C, 2 instructions, 8 bytes.
   Returns +0x1E4. */

typedef struct { u8 pad0[0x1E4]; s32 field_1E4; } Obj;
s32 func_024D8B68(Obj *self) { return self->field_1E4; }
