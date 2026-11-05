#include "block.h"

/* 0x023D2508 .. 0x023D250C, 2 instructions, 8 bytes.
   Returns byte +0x26C. */

typedef struct { u8 pad0[0x26C]; u8 field_26C; } Obj;
u8 func_023D2508(Obj *self) { return self->field_26C; }
