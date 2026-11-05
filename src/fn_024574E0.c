#include "block.h"

/* 0x024574E0 .. 0x024574E4, 2 instructions, 8 bytes.
   Returns float +0x1C08. */

typedef struct { u8 pad0[0x1C08]; f32 field_1C08; } Obj;
f32 func_024574E0(Obj *self) { return self->field_1C08; }
