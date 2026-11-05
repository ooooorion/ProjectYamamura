#include "block.h"

/* 0x024C2350 .. 0x024C2354, 2 instructions, 8 bytes.
   Stores byte +0xBC. */

typedef struct { u8 pad0[0xBC]; s8 field_BC; } Obj;
void func_024C2350(Obj *self, s8 value) { self->field_BC = value; }
