#include "block.h"

/* 0x023EED1C .. 0x023EED24, 2 instructions, 8 bytes.
   Returns byte +0x6AE. */

typedef struct { u8 pad0[0x6AE]; u8 field_6AE; } Obj;
u8 func_023EED1C(Obj *self) { return self->field_6AE; }
