#include "block.h"

/* 0x0250BEF4 .. 0x0250BEFC, 3 instructions, 12 bytes.
   Stores the nested +0xA90 field. */

typedef struct { u8 pad0[0x7C]; void *field_7C; } Obj;
void func_0250BEF4(Obj *self, s32 value) {
    *(s32 *)((u8 *)self->field_7C + 0xA90) = value;
}
