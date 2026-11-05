#include "block.h"

/* 0x02533440 .. 0x02533444, 2 instructions, 8 bytes. */

typedef struct { u8 pad0[0xD0]; s32 field_D0; } Obj;
void func_02533440(Obj *self, s32 value) { self->field_D0 = value; }
