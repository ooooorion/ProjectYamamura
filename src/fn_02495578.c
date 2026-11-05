#include "block.h"

/* 0x02495578 .. 0x02495580, 3 instructions, 12 bytes.
   Sets byte +0x294. */

typedef struct { u8 pad0[0x294]; s8 field_294; } Obj;
void func_02495578(Obj *self) { self->field_294 = 1; }
