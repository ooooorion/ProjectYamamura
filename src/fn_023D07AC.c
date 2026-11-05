#include "block.h"

/* 0x023D07AC .. 0x023D07B0, 2 instructions, 8 bytes.
   Returns byte +0x238. */

typedef struct { u8 pad0[0x238]; u8 field_238; } Obj;
u8 func_023D07AC(Obj *self) { return self->field_238; }
