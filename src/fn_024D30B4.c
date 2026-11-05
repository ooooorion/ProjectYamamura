#include "block.h"

/* 0x024D30B4 .. 0x024D30C0, 4 instructions, 16 bytes.
   True when +0x178 is zero. */

typedef struct { u8 pad0[0x178]; s32 field_178; } Obj;
s32 func_024D30B4(Obj *self) { return self->field_178 == 0; }
