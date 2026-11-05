#include "block.h"

/* 0x02464768 .. 0x0246476C, 2 instructions, 8 bytes.
   Stores +0xA34. */

typedef struct { u8 pad0[0xA34]; s32 field_A34; } Obj;
void func_02464768(Obj *self, s32 value) { self->field_A34 = value; }
