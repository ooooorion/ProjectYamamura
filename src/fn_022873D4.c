#include "block.h"

/* 0x022873D4 .. 0x022873E0, 4 instructions, 16 bytes.
   Tests the word at +0x214 for zero. */

typedef struct { u8 pad0[0x214]; s32 field_214; } Obj;
s32 func_022873D4(Obj *self) { return self->field_214 == 0; }
