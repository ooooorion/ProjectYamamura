#include "block.h"

/* 0x02528D50 .. 0x02528D54, 2 instructions, 8 bytes. */

typedef struct { u8 pad0[8]; f32 field_8; } Obj;
f32 func_02528D50(Obj *self) { return self->field_8; }
