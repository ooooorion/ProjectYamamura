#include "block.h"

/* 0x023D7B18 .. 0x023D7B1C, 2 instructions, 8 bytes.
   Returns byte +0x274. */

typedef struct { u8 pad0[0x274]; u8 field_274; } Obj;
u8 func_023D7B18(Obj *self) { return self->field_274; }
