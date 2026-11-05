#include "block.h"

/* 0x02527100 .. 0x02527110, 5 instructions, 20 bytes. */

typedef struct { u8 pad0[0x24]; s32 field_24; } Obj;
s32 func_02527100(Obj *self) { return (self->field_24 ^ 2) == 0; }
