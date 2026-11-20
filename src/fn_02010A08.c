#include "block.h"

/* 0x02010A08 .. 0x02010A14, 3 instructions, 12 bytes.
   Sets byte +0x1A4. */

typedef struct { u8 pad0[0x1A4]; u8 field_1A4; } Obj;
void func_02010A08(Obj *self) { self->field_1A4 = 1; }
