#include "block.h"

/* 0x0245EDD8 .. 0x0245EDDC, 2 instructions, 8 bytes.
   Returns +0x32C. */

typedef struct { u8 pad0[0x32C]; s32 field_32C; } Obj;
s32 func_0245EDD8(Obj *self) { return self->field_32C; }
