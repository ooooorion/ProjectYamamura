#include "block.h"

/* 0x023A3F64 .. 0x023A3F6C, 3 instructions, 12 bytes.
   Stores two adjacent words. */

typedef struct { u8 pad0[0x78]; s32 field_78; s32 field_7C; } Obj;
void func_023A3F64(Obj *self, s32 first, s32 second) {
    self->field_78 = first;
    self->field_7C = second;
}
