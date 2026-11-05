#include "block.h"

/* 0x024D55D0 .. 0x024D55D4, 2 instructions, 8 bytes.
   Returns +0x1EC. */

typedef struct { u8 pad0[0x1EC]; s32 field_1EC; } Obj;
s32 func_024D55D0(Obj *self) { return self->field_1EC; }
