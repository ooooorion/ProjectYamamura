#include "block.h"

/* 0x022F3280 .. 0x022F3288, 3 instructions, 12 bytes.
   Loads through the +4 pointer from +0xCF0. */

typedef struct { u8 pad0[0xCF0]; s32 field_CF0; } Sub;
typedef struct { u8 pad0[4]; Sub *field_4; } Obj;
s32 func_022F3280(Obj *self) { return self->field_4->field_CF0; }
