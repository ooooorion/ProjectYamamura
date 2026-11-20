#include "block.h"

/* 0x023EF25C .. 0x023EF264, 2 instructions, 8 bytes.
   Returns byte +0x6BB. */

typedef struct { u8 pad0[0x6BB]; u8 field_6BB; } Obj;
u8 func_023EF25C(Obj *self) { return self->field_6BB; }
