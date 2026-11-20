#include "block.h"

/* 0x029CB608 .. 0x029CB610, 2 instructions, 8 bytes.
   Returns word +0x118. */

typedef struct { u8 pad0[0x118]; s32 field_118; } Obj;
s32 func_029CB608(Obj *self) { return self->field_118; }
