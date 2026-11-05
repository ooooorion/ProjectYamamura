#include "block.h"

/* 0x02457BA4 .. 0x02457BA8, 2 instructions, 8 bytes.
   Stores byte +0x1C51. */

typedef struct { u8 pad0[0x1C51]; s8 field_1C51; } Obj;
void func_02457BA4(Obj *self, s8 value) { self->field_1C51 = value; }
