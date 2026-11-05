#include "block.h"

/* 0x024C23BC .. 0x024C23C0, 2 instructions, 8 bytes.
   Stores +0xAC. */

typedef struct { u8 pad0[0xAC]; s32 field_AC; } Obj;
void func_024C23BC(Obj *self, s32 value) { self->field_AC = value; }
