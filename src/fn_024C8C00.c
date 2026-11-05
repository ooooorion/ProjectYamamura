#include "block.h"

/* 0x024C8C00 .. 0x024C8C04, 2 instructions, 8 bytes.
   Returns +0x78. */

typedef struct { u8 pad0[0x78]; s32 field_78; } Obj;
s32 func_024C8C00(Obj *self) { return self->field_78; }
