#include "block.h"

/* 0x024EBA48 .. 0x024EBA4C, 2 instructions, 8 bytes.
   Stores +0xD4. */

typedef struct { u8 pad0[0xD4]; s32 field_D4; } Obj;
void func_024EBA48(Obj *self, s32 value) { self->field_D4 = value; }
