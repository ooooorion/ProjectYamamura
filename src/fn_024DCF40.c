#include "block.h"

/* 0x024DCF40 .. 0x024DCF44, 2 instructions, 8 bytes.
   Returns byte +0x111. */

typedef struct { u8 pad0[0x111]; u8 field_111; } Obj;
u8 func_024DCF40(Obj *self) { return self->field_111; }
