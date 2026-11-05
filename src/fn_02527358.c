#include "block.h"

/* 0x02527358 .. 0x02527368, 5 instructions, 20 bytes. */

typedef struct { u8 pad0[0x24]; s32 field_24; } Obj;
s32 func_02527358(Obj *self) { return (self->field_24 ^ 3) == 0; }
