#include "block.h"

/* 0x02B853C8 .. 0x02B853D0, 2 instructions, 8 bytes.
   Stores +0xC. */

typedef struct { u8 pad0[0xC]; s32 field_C; } Obj;
void func_02B853C8(Obj *self, s32 value) { self->field_C = value; }
