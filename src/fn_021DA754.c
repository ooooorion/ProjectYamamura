#include "block.h"

/* 0x021DA754 .. 0x021DA764, 5 instructions, 20 bytes.
   True unless +0x4F4 is four. */

typedef struct { u8 pad0[0x4F4]; s32 field_4F4; } Obj;
s32 func_021DA754(Obj *self) { return self->field_4F4 != 4; }
