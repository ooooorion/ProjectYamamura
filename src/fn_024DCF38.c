#include "block.h"

/* 0x024DCF38 .. 0x024DCF3C, 2 instructions, 8 bytes.
   Stores byte +0x111. */

typedef struct { u8 pad0[0x111]; s8 field_111; } Obj;
void func_024DCF38(Obj *self, s8 value) { self->field_111 = value; }
