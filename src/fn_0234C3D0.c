#include "block.h"

/* 0x0234C3D0 .. 0x0234C3D8, 3 instructions, 12 bytes.
   Clears the word at +0x28C. */

typedef struct { u8 pad0[0x28C]; s32 field_28C; } Obj;
void func_0234C3D0(Obj *self) { self->field_28C = 0; }
