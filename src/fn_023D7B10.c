#include "block.h"

/* 0x023D7B10 .. 0x023D7B14, 2 instructions, 8 bytes.
   Returns byte +0x277. */

typedef struct { u8 pad0[0x277]; u8 field_277; } Obj;
u8 func_023D7B10(Obj *self) { return self->field_277; }
