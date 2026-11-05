#include "block.h"

/* 0x021D513C .. 0x021D514C, 5 instructions, 20 bytes.
   True when +0x578 is one. */

typedef struct { u8 pad0[0x578]; s32 field_578; } Obj;
s32 func_021D513C(Obj *self) { return (self->field_578 ^ 1) == 0; }
