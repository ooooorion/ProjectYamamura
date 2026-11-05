#include "block.h"

/* 0x024E056C .. 0x024E0570, 2 instructions, 8 bytes.
   Returns byte +0x33. */

typedef struct { u8 pad0[0x33]; u8 field_33; } Obj;
u8 func_024E056C(Obj *self) { return self->field_33; }
