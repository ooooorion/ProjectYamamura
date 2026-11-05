#include "block.h"

/* 0x0245FDE4 .. 0x0245FDE8, 2 instructions, 8 bytes.
   Returns byte +0x353. */

typedef struct { u8 pad0[0x353]; u8 field_353; } Obj;
u8 func_0245FDE4(Obj *self) { return self->field_353; }
