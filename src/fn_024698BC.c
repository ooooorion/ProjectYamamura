#include "block.h"

/* 0x024698BC .. 0x024698C0, 2 instructions, 8 bytes.
   Stores +0x208. */

typedef struct { u8 pad0[0x208]; s32 field_208; } Obj;
void func_024698BC(Obj *self, s32 value) { self->field_208 = value; }
