#include "block.h"

/* 0x023EED84 .. 0x023EED8C, 2 instructions, 8 bytes.
   Returns byte +0x70F. */

typedef struct { u8 pad0[0x70F]; u8 field_70F; } Obj;
u8 func_023EED84(Obj *self) { return self->field_70F; }
