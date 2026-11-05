#include "block.h"

/* 0x021D6D6C .. 0x021D6D74, 3 instructions, 12 bytes.
   Sets the +0x58D byte. */

typedef struct { u8 pad0[0x58D]; s8 field_58D; } Obj;
void func_021D6D6C(Obj *self) { self->field_58D = 1; }
