#include "block.h"

/* 0x024DF738 .. 0x024DF748, 5 instructions, 20 bytes.
   Stores the pair at +0x28. */

typedef struct { u8 pad0[0x28]; s32 field_28; s32 field_2C; } Obj;
void func_024DF738(Obj *self, s32 *arg1, s32 *arg2) {
    self->field_28 = *arg1;
    self->field_2C = *arg2;
}
