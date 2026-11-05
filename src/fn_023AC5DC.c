#include "block.h"

/* 0x023AC5DC .. 0x023AC5EC, 5 instructions, 20 bytes.
   True when +0x1E8 is two. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_023AC5DC(Obj *self) { return (self->field_1E8 ^ 2) == 0; }
