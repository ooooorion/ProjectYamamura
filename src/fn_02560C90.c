#include "block.h"

/* 0x02560C90 .. 0x02560C98, 3 instructions, 12 bytes. */

typedef struct { u8 pad0[0x1914]; s32 field_1914; } Obj;
void func_02560C90(Obj *self) { self->field_1914 = 0x12C; }
