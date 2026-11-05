#include "block.h"

/* 0x024C8970 .. 0x024C8974, 2 instructions, 8 bytes.
   Returns +0x12F0. */

typedef struct { u8 pad0[0x12F0]; s32 field_12F0; } Obj;
s32 func_024C8970(Obj *self) { return self->field_12F0; }
