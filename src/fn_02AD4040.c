#include "block.h"

/* 0x02AD4040 .. 0x02AD4048, 2 instructions, 8 bytes.
   Returns word +0x100. */

typedef struct { u8 pad0[0x100]; s32 field_100; } Obj;
s32 func_02AD4040(Obj *self) { return self->field_100; }
