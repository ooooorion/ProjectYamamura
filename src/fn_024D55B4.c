#include "block.h"

/* 0x024D55B4 .. 0x024D55B8, 2 instructions, 8 bytes.
   Returns +0x1DC. */

typedef struct { u8 pad0[0x1DC]; s32 field_1DC; } Obj;
s32 func_024D55B4(Obj *self) { return self->field_1DC; }
