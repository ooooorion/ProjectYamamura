#include "block.h"

/* 0x024CB1B0 .. 0x024CB1B4, 2 instructions, 8 bytes.
   Returns byte +0x1330. */

typedef struct { u8 pad0[0x1330]; u8 field_1330; } Obj;
u8 func_024CB1B0(Obj *self) { return self->field_1330; }
