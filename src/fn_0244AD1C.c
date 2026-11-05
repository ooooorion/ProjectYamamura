#include "block.h"

/* 0x0244AD1C .. 0x0244AD68, 20 instructions, 80 bytes.
   True when the object is inactive and its stored resource probe succeeds. */

typedef struct { u8 pad0[0x118]; s32 field_118; u8 pad11C[0x820]; s32 field_93C; } Obj;
extern s32 func_02025B94(s32 value);
s32 func_0244AD1C(Obj *self) {
    if (!(self->field_118 & 2) && func_02025B94(self->field_93C) == 0) return 1;
    return 0;
}
