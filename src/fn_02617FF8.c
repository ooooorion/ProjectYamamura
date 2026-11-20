#include "block.h"

/* 0x02617FF8 .. 0x02618000, 2 instructions, 8 bytes.
   Returns byte +0x4AD. */

typedef struct { u8 pad0[0x4AD]; u8 field_4AD; } Obj;
u8 func_02617FF8(Obj *self) { return self->field_4AD; }
