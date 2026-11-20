#include "block.h"

/* 0x024F19A8 .. 0x024F19B4, 3 instructions, 12 bytes.
   Stores two words at +0x248 and +0x24C. */

typedef struct { u8 pad0[0x248]; s32 field_248; s32 field_24C; } Obj;
void func_024F19A8(Obj *self, s32 unused, s32 first, s32 second) {
    self->field_248 = first;
    self->field_24C = second;
}
