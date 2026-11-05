#include "block.h"

/* 0x024DF77C .. 0x024DF780, 2 instructions, 8 bytes.
   Returns byte +0x32. */

typedef struct { u8 pad0[0x32]; u8 field_32; } Obj;
u8 func_024DF77C(Obj *self) { return self->field_32; }
