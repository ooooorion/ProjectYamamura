#include "block.h"

/* 0x024BF630 .. 0x024BF640, 5 instructions, 20 bytes.
   True when the type field is two. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_024BF630(Obj *self) { return (self->field_1E8 ^ 2) == 0; }
