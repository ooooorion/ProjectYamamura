#include "block.h"

/* 0x023EEC34 .. 0x023EEC38, 2 instructions, 8 bytes.
   Returns byte +0x69F. */

typedef struct { u8 pad0[0x69F]; u8 field_69F; } Obj;
u8 func_023EEC34(Obj *self) { return self->field_69F; }
