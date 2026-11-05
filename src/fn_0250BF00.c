#include "block.h"

/* 0x0250BF00 .. 0x0250BF08, 3 instructions, 12 bytes.
   Returns the nested +0xA90 field. */

typedef struct { u8 pad0[0x7C]; void *field_7C; } Obj;
s32 func_0250BF00(Obj *self) {
    return *(s32 *)((u8 *)self->field_7C + 0xA90);
}
