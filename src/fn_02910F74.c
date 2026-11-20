#include "block.h"

/* 0x02910F74 .. 0x02910F7C, 2 instructions, 8 bytes.
   Returns word at offset zero. */

typedef struct { s32 field_0; } Obj;
s32 func_02910F74(Obj *self) { return self->field_0; }
