#include "block.h"

/* 0x024CB210 .. 0x024CB21C, 4 instructions, 16 bytes.
   True when the state field is zero. */

typedef struct { u8 pad0[0xC]; s32 field_C; } Obj;
s32 func_024CB210(Obj *self) { return self->field_C == 0; }
