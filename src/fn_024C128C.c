#include "block.h"

/* 0x024C128C .. 0x024C1290, 2 instructions, 8 bytes.
   Stores +0xA4. */

typedef struct { u8 pad0[0xA4]; s32 field_A4; } Obj;
void func_024C128C(Obj *self, s32 value) { self->field_A4 = value; }
