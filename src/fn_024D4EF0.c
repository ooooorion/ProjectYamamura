#include "block.h"

/* 0x024D4EF0 .. 0x024D4EF4, 2 instructions, 8 bytes.
   Returns byte +0x3EC. */

typedef struct { u8 pad0[0x3EC]; u8 field_3EC; } Obj;
u8 func_024D4EF0(Obj *self) { return self->field_3EC; }
