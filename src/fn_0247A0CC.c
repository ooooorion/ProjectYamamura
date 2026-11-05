#include "block.h"

/* 0x0247A0CC .. 0x0247A0D8, 4 instructions, 16 bytes.
   True when the type field is zero. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_0247A0CC(Obj *self) { return self->field_1E8 == 0; }
