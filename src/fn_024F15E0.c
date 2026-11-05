#include "block.h"

/* 0x024F15E0 .. 0x024F15E4, 2 instructions, 8 bytes.
   Returns byte +0x323. */

typedef struct { u8 pad0[0x323]; u8 field_323; } Obj;
u8 func_024F15E0(Obj *self) { return self->field_323; }
