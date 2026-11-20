#include "block.h"

/* 0x024DCF18 .. 0x024DCF24, 3 instructions, 12 bytes.
   Sets byte +0x139. */

typedef struct { u8 pad0[0x139]; u8 field_139; } Obj;
void func_024DCF18(Obj *self) { self->field_139 = 255; }
