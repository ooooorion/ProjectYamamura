#include "block.h"

/* 0x021FF118 .. 0x021FF124, 4 instructions, 16 bytes.
   Clears +0x18 and +0x7C. */

typedef struct { u8 pad0[0x18]; s32 field_18; u8 pad1C[0x60]; s32 field_7C; } Obj;
void func_021FF118(Obj *self) { self->field_18 = 0; self->field_7C = 0; }
