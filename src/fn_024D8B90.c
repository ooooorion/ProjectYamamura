#include "block.h"

/* 0x024D8B90 .. 0x024D8B94, 2 instructions, 8 bytes.
   Returns byte +0x3EA. */

typedef struct { u8 pad0[0x3EA]; u8 field_3EA; } Obj;
u8 func_024D8B90(Obj *self) { return self->field_3EA; }
