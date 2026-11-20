#include "block.h"

/* 0x023EED24 .. 0x023EED2C, 2 instructions, 8 bytes.
   Returns byte +0x6C0. */

typedef struct { u8 pad0[0x6C0]; u8 field_6C0; } Obj;
u8 func_023EED24(Obj *self) { return self->field_6C0; }
