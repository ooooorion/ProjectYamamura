#include "block.h"

/* 0x0250BEC8 .. 0x0250BED0, 3 instructions, 12 bytes.
   Stores the nested +0xA84 field. */

typedef struct { u8 pad0[0x7C]; void *field_7C; } Obj;
void func_0250BEC8(Obj *self, s32 value) {
    *(s32 *)((u8 *)self->field_7C + 0xA84) = value;
}
