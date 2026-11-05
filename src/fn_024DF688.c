#include "block.h"

/* 0x024DF688 .. 0x024DF68C, 2 instructions, 8 bytes.
   Returns +0x20. */

typedef struct { u8 pad0[0x20]; s32 field_20; } Obj;
s32 func_024DF688(Obj *self) { return self->field_20; }
