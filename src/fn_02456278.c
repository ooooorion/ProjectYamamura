#include "block.h"

/* 0x02456278 .. 0x0245627C, 2 instructions, 8 bytes.
   Returns +0x1C20. */

typedef struct { u8 pad0[0x1C20]; s32 field_1C20; } Obj;
s32 func_02456278(Obj *self) { return self->field_1C20; }
