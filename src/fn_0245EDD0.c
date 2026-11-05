#include "block.h"

/* 0x0245EDD0 .. 0x0245EDD4, 2 instructions, 8 bytes.
   Returns +0x328. */

typedef struct { u8 pad0[0x328]; s32 field_328; } Obj;
s32 func_0245EDD0(Obj *self) { return self->field_328; }
