#include "block.h"

/* 0x029E2038 .. 0x029E2044, 3 instructions, 12 bytes.
   Sets byte +0x1D. */

typedef struct { u8 pad0[0x1D]; u8 field_1D; } Obj;
void func_029E2038(Obj *self) { self->field_1D = 1; }
