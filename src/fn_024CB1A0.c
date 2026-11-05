#include "block.h"

/* 0x024CB1A0 .. 0x024CB1A4, 2 instructions, 8 bytes.
   Stores float +0x12AC. */

typedef struct { u8 pad0[0x12AC]; f32 field_12AC; } Obj;
void func_024CB1A0(Obj *self, f32 value) { self->field_12AC = value; }
