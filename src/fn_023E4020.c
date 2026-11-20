#include "block.h"

/* 0x023E4020 .. 0x023E4030, 4 instructions, 16 bytes.
   True when +0x18 is zero. */

typedef struct { u8 pad0[0x18]; u32 field_18; } Obj;
s32 func_023E4020(Obj *self) { return self->field_18 == 0; }
