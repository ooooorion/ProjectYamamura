#include "block.h"

/* 0x02497D50 .. 0x02497D58, 3 instructions, 12 bytes.
   Sets byte +0x28D. */

typedef struct { u8 pad0[0x28D]; s8 field_28D; } Obj;
void func_02497D50(Obj *self) { self->field_28D = 1; }
