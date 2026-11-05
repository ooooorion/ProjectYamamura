#include "block.h"

/* 0x024F17FC .. 0x024F1800, 2 instructions, 8 bytes.
   Returns +0x23C. */

typedef struct { u8 pad0[0x23C]; s32 field_23C; } Obj;
s32 func_024F17FC(Obj *self) { return self->field_23C; }
