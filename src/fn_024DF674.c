#include "block.h"

/* 0x024DF674 .. 0x024DF684, 5 instructions, 20 bytes.
   Stores the pair at +0x20. */

typedef struct { u8 pad0[0x20]; s32 field_20; s32 field_24; } Obj;
void func_024DF674(Obj *self, s32 *arg1, s32 *arg2) {
    self->field_20 = *arg1;
    self->field_24 = *arg2;
}
