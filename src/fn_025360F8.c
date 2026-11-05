#include "block.h"

/* 0x025360F8 .. 0x02536100, 3 instructions, 12 bytes. */

typedef struct { u8 pad0[0x14]; s32 field_14; } Obj;
void func_025360F8(Obj *self) { self->field_14 = 0; }
