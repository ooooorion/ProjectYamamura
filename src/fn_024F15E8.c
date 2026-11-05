#include "block.h"

/* 0x024F15E8 .. 0x024F15EC, 2 instructions, 8 bytes.
   Returns byte +0x324. */

typedef struct { u8 pad0[0x324]; u8 field_324; } Obj;
u8 func_024F15E8(Obj *self) { return self->field_324; }
