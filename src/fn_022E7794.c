#include "block.h"

/* 0x022E7794 .. 0x022E77A0, 4 instructions, 16 bytes.
   Clears the byte at +8 and the word at +4. */

typedef struct { u8 pad0[4]; s32 field_4; s8 field_8; } Obj;
void func_022E7794(Obj *self) { self->field_8 = 0; self->field_4 = 0; }
