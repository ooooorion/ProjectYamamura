#include "block.h"

/* 0x024426C4 .. 0x024426D4, 5 instructions, 20 bytes.
   True when +0x2C4 is five. */

typedef struct { u8 pad0[0x2C4]; s32 field_2C4; } Obj;
s32 func_024426C4(Obj *self) { return (self->field_2C4 ^ 5) == 0; }
