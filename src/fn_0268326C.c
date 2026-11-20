#include "block.h"

/* 0x0268326C .. 0x02683274, 2 instructions, 8 bytes.
   Returns word +0x6C. */

typedef struct { u8 pad0[0x6C]; s32 field_6C; } Obj;
s32 func_0268326C(Obj *self) { return self->field_6C; }
