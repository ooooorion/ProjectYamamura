#include "block.h"

/* 0x02457BAC .. 0x02457BB0, 2 instructions, 8 bytes.
   Returns byte +0x1C50. */

typedef struct { u8 pad0[0x1C50]; u8 field_1C50; } Obj;
u8 func_02457BAC(Obj *self) { return self->field_1C50; }
