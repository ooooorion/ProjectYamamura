#include "block.h"

/* 0x023880B8 .. 0x023880C0, 3 instructions, 12 bytes.
   Sets the byte at +0x1F. */

typedef struct { u8 pad0[0x1F]; s8 field_1F; } Obj;
void func_023880B8(Obj *self) { self->field_1F = 1; }
