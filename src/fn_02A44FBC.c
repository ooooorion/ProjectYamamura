#include "block.h"

/* 0x02A44FBC .. 0x02A44FC8, 3 instructions, 12 bytes.
   Clears word +0x28. */

typedef struct { u8 pad0[0x28]; s32 field_28; } Obj;
void func_02A44FBC(Obj *self) { self->field_28 = 0; }
