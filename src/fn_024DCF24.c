#include "block.h"

/* 0x024DCF24 .. 0x024DCF34, 5 instructions, 20 bytes.
   True when byte +0x139 is not 0xFF. */

typedef struct { u8 pad0[0x139]; u8 field_139; } Obj;
s32 func_024DCF24(Obj *self) { return self->field_139 != 0xFF; }
