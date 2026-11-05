#include "block.h"

/* 0x0248381C .. 0x0248382C, 5 instructions, 20 bytes.
   True when +0x1FC is seven. */

typedef struct { u8 pad0[0x1FC]; s32 field_1FC; } Obj;
s32 func_0248381C(Obj *self) { return (self->field_1FC ^ 7) == 0; }
