#include "block.h"

/* 0x024D30A0 .. 0x024D30B0, 5 instructions, 20 bytes.
   True when +0x178 is seven. */

typedef struct { u8 pad0[0x178]; s32 field_178; } Obj;
s32 func_024D30A0(Obj *self) { return (self->field_178 ^ 7) == 0; }
