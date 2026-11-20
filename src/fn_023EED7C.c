#include "block.h"

/* 0x023EED7C .. 0x023EED84, 2 instructions, 8 bytes.
   Returns byte +0x6A8. */

typedef struct { u8 pad0[0x6A8]; u8 field_6A8; } Obj;
u8 func_023EED7C(Obj *self) { return self->field_6A8; }
