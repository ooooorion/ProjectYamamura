#include "block.h"

/* 0x024E03A4 .. 0x024E03BC, 7 instructions, 28 bytes.
   True when the nested +0x21C state is not four. */

typedef struct { u8 pad0[0x10]; void *field_10; } Obj;
typedef struct { u8 pad0[0x2BC]; void *field_2BC; } Mid;
typedef struct { u8 pad0[0x21C]; s32 field_21C; } Deep;
s32 func_024E03A4(Obj *self) {
    Mid *mid;
    Deep *deep;

    mid = self->field_10;
    deep = mid->field_2BC;
    return deep->field_21C != 4;
}
