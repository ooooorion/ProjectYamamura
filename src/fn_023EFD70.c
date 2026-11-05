#include "block.h"

/* 0x023EFD70 .. 0x023EFD80, 5 instructions, 20 bytes.
   True when +0x1E8 is 0x41. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_023EFD70(Obj *self) { return (self->field_1E8 ^ 0x41) == 0; }
