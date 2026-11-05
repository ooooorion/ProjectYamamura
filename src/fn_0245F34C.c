#include "block.h"

/* 0x0245F34C .. 0x0245F350, 2 instructions, 8 bytes.
   Returns float +0x314. */

typedef struct { u8 pad0[0x314]; f32 field_314; } Obj;
f32 func_0245F34C(Obj *self) { return self->field_314; }
