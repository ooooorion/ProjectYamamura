#include "block.h"

/* 0x024DF65C .. 0x024DF660, 2 instructions, 8 bytes.
   Returns +0x1C. */

typedef struct { u8 pad0[0x1C]; s32 field_1C; } Obj;
s32 func_024DF65C(Obj *self) { return self->field_1C; }
