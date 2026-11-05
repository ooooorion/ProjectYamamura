#include "block.h"

/* 0x02344634 .. 0x0234463C, 3 instructions, 12 bytes.
   Clears the byte at +0x41. */

typedef struct { u8 pad0[0x41]; s8 field_41; } Obj;
void func_02344634(Obj *self) { self->field_41 = 0; }
