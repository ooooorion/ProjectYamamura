#include "block.h"

/* 0x02531180 .. 0x02531184, 2 instructions, 8 bytes. */

typedef struct { u8 pad0[0x98]; s32 field_98; } Obj;
void func_02531180(Obj *self, s32 value) { self->field_98 = value; }
