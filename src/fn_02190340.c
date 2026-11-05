#include "block.h"

/* 0x02190340 .. 0x02190348, 3 instructions, 12 bytes.
   Clears the word at +0x510. */

typedef struct { u8 pad0[0x510]; s32 field_510; } Obj;
void func_02190340(Obj *self) { self->field_510 = 0; }
