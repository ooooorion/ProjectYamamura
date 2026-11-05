#include "block.h"

/* 0x023CC814 .. 0x023CC820, 4 instructions, 16 bytes.
   True when +0xC is zero. */

typedef struct { u8 pad0[0xC]; s32 field_C; } Obj;
s32 func_023CC814(Obj *self) { return self->field_C == 0; }
