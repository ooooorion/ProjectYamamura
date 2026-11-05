#include "block.h"

/* 0x0245EF20 .. 0x0245EF24, 2 instructions, 8 bytes.
   Returns +0x334. */

typedef struct { u8 pad0[0x334]; s32 field_334; } Obj;
s32 func_0245EF20(Obj *self) { return self->field_334; }
