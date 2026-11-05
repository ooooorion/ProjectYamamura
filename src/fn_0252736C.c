#include "block.h"

/* 0x0252736C .. 0x0252737C, 5 instructions, 20 bytes. */

typedef struct { u8 pad0[0x24]; s32 field_24; } Obj;
s32 func_0252736C(Obj *self) { return (self->field_24 ^ 4) == 0; }
