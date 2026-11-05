#include "block.h"

/* 0x024DCF10 .. 0x024DCF14, 2 instructions, 8 bytes.
   Returns byte +0x139. */

typedef struct { u8 pad0[0x139]; u8 field_139; } Obj;
u8 func_024DCF10(Obj *self) { return self->field_139; }
