#include "block.h"

/* 0x02531178 .. 0x0253117C, 2 instructions, 8 bytes. */

typedef struct { u8 pad0[0x94]; s32 field_94; } Obj;
void func_02531178(Obj *self, s32 value) { self->field_94 = value; }
