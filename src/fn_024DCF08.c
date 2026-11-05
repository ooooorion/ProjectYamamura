#include "block.h"

/* 0x024DCF08 .. 0x024DCF0C, 2 instructions, 8 bytes.
   Stores byte +0x139. */

typedef struct { u8 pad0[0x139]; s8 field_139; } Obj;
void func_024DCF08(Obj *self, s8 value) { self->field_139 = value; }
