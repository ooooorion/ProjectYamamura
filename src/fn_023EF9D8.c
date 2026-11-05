#include "block.h"

/* 0x023EF9D8 .. 0x023EF9E8, 5 instructions, 20 bytes.
   True unless +0x1E8 is 0x61. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_023EF9D8(Obj *self) { return self->field_1E8 != 0x61; }
