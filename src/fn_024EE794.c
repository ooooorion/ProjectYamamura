#include "block.h"

/* 0x024EE794 .. 0x024EE798, 2 instructions, 8 bytes.
   Stores +0x234. */

typedef struct { u8 pad0[0x234]; s32 field_234; } Obj;
void func_024EE794(Obj *self, s32 value) { self->field_234 = value; }
