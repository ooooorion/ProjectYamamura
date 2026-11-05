#include "block.h"

/* 0x024907A0 .. 0x024907A4, 2 instructions, 8 bytes.
   Returns +0x220. */

typedef struct { u8 pad0[0x220]; s32 field_220; } Obj;
s32 func_024907A0(Obj *self) { return self->field_220; }
