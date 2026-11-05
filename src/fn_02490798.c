#include "block.h"

/* 0x02490798 .. 0x0249079C, 2 instructions, 8 bytes.
   Returns +0x21C. */

typedef struct { u8 pad0[0x21C]; s32 field_21C; } Obj;
s32 func_02490798(Obj *self) { return self->field_21C; }
