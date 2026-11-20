#include "block.h"

/* 0x023EEC2C .. 0x023EEC34, 2 instructions, 8 bytes.
   Returns byte +0x69C. */

typedef struct { u8 pad0[0x69C]; u8 field_69C; } Obj;
u8 func_023EEC2C(Obj *self) { return self->field_69C; }
