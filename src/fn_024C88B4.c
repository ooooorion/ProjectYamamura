#include "block.h"

/* 0x024C88B4 .. 0x024C88E0, 12 instructions, 48 bytes.
   Returns the indexed byte, or -1 when the index is out of range. */

typedef struct { u8 pad0[0xA0]; s32 field_A0; u8 *field_A4; } Obj;
s8 func_024C88B4(Obj *self, s32 index) {
    s32 count;
    u8 *table;

    count = self->field_A0;
    if (index >= count) return -1;
    table = self->field_A4;
    if ((u32)index < (u32)count) table += index;
    return (s8)*table;
}
