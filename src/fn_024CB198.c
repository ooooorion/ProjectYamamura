#include "block.h"

/* 0x024CB198 .. 0x024CB19C, 2 instructions, 8 bytes.
   Stores float +0x12A8. */

typedef struct { u8 pad0[0x12A8]; f32 field_12A8; } Obj;
void func_024CB198(Obj *self, f32 value) { self->field_12A8 = value; }
