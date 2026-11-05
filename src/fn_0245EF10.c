#include "block.h"

/* 0x0245EF10 .. 0x0245EF14, 2 instructions, 8 bytes.
   Returns +0x330. */

typedef struct { u8 pad0[0x330]; s32 field_330; } Obj;
s32 func_0245EF10(Obj *self) { return self->field_330; }
