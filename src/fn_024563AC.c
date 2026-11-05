#include "block.h"

/* 0x024563AC .. 0x024563B0, 2 instructions, 8 bytes.
   Stores +0x234. */

typedef struct { u8 pad0[0x234]; s32 field_234; } Obj;
void func_024563AC(Obj *self, s32 value) { self->field_234 = value; }
