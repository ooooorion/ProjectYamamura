#include "block.h"

/* 0x021D6D58 .. 0x021D6D68, 5 instructions, 20 bytes.
   Sets +0x58C and clears +0x58D. */

typedef struct { u8 pad0[0x58C]; s8 field_58C; s8 field_58D; } Obj;
void func_021D6D58(Obj *self) { self->field_58C = 1; self->field_58D = 0; }
