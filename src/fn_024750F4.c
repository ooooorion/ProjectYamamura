#include "block.h"

/* 0x024750F4 .. 0x024750FC, 2 instructions, 8 bytes.
   Stores +0x288. */

typedef struct { u8 pad0[0x288]; s32 field_288; } Obj;
void func_024750F4(Obj *self, s32 value) { self->field_288 = value; }
