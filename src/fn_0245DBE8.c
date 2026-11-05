#include "block.h"

/* 0x0245DBE8 .. 0x0245DBF8, 5 instructions, 20 bytes.
   True when +0x21C is two. */

typedef struct { u8 pad0[0x21C]; s32 field_21C; } Obj;
s32 func_0245DBE8(Obj *self) { return (self->field_21C ^ 2) == 0; }
