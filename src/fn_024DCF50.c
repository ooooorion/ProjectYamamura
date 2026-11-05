#include "block.h"

/* 0x024DCF50 .. 0x024DCF54, 2 instructions, 8 bytes.
   Returns byte +0x112. */

typedef struct { u8 pad0[0x112]; u8 field_112; } Obj;
u8 func_024DCF50(Obj *self) { return self->field_112; }
