#include "block.h"

/* 0x0282C974 .. 0x0282C97C, 2 instructions, 8 bytes.
   Returns float +0x38. */

typedef struct { u8 pad0[0x38]; f32 field_38; } Obj;
f32 func_0282C974(Obj *self) { return self->field_38; }
