#include "block.h"

/* 0x023D2538 .. 0x023D253C, 2 instructions, 8 bytes.
   Returns byte +0x26E. */

typedef struct { u8 pad0[0x26E]; u8 field_26E; } Obj;
u8 func_023D2538(Obj *self) { return self->field_26E; }
