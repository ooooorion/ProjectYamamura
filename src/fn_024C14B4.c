#include "block.h"

/* 0x024C14B4 .. 0x024C14BC, 3 instructions, 12 bytes.
   Sets byte +0xB4. */

typedef struct { u8 pad0[0xB4]; s8 field_B4; } Obj;
void func_024C14B4(Obj *self) { self->field_B4 = 1; }
