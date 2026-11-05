#include "block.h"

/* 0x024F1990 .. 0x024F1994, 2 instructions, 8 bytes.
   Returns byte +0x325. */

typedef struct { u8 pad0[0x325]; u8 field_325; } Obj;
u8 func_024F1990(Obj *self) { return self->field_325; }
