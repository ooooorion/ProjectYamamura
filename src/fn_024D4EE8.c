#include "block.h"

/* 0x024D4EE8 .. 0x024D4EEC, 2 instructions, 8 bytes.
   Returns byte +0x3E5. */

typedef struct { u8 pad0[0x3E5]; u8 field_3E5; } Obj;
u8 func_024D4EE8(Obj *self) { return self->field_3E5; }
