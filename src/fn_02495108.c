#include "block.h"

/* 0x02495108 .. 0x02495118, 5 instructions, 20 bytes.
   True when the type field is three. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_02495108(Obj *self) { return (self->field_1E8 ^ 3) == 0; }
