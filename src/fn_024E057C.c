#include "block.h"

/* 0x024E057C .. 0x024E0580, 2 instructions, 8 bytes.
   Returns byte +0x34. */

typedef struct { u8 pad0[0x34]; u8 field_34; } Obj;
u8 func_024E057C(Obj *self) { return self->field_34; }
