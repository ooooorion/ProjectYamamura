#include "block.h"

/* 0x02ACCB54 .. 0x02ACCB5C, 2 instructions, 8 bytes.
   Returns word +0x10. */

typedef struct { u8 pad0[0x10]; s32 field_10; } Obj;
s32 func_02ACCB54(Obj *self) { return self->field_10; }
