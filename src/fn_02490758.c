#include "block.h"

/* 0x02490758 .. 0x02490768, 5 instructions, 20 bytes.
   True when +0x734 is five. */

typedef struct { u8 pad0[0x734]; s32 field_734; } Obj;
s32 func_02490758(Obj *self) { return (self->field_734 ^ 5) == 0; }
