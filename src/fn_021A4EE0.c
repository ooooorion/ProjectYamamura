#include "block.h"

/* 0x021A4EE0 .. 0x021A4EF8, 7 instructions, 28 bytes.
   Clears +0x50B when set and returns one. */

typedef struct { u8 pad0[0x50B]; u8 field_50B; } Obj;
s32 func_021A4EE0(Obj *self) {
    if (self->field_50B != 0) self->field_50B = 0;
    return 1;
}
