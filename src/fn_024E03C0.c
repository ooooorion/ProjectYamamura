#include "block.h"

/* 0x024E03C0 .. 0x024E03CC, 4 instructions, 16 bytes.
   Returns the nested +0x1FC state. */

typedef struct { u8 pad0[0x10]; void *field_10; } Obj;
typedef struct { u8 pad0[0x2BC]; void *field_2BC; } Mid;
typedef struct { u8 pad0[0x1FC]; s32 field_1FC; } Deep;
s32 func_024E03C0(Obj *self) {
    Mid *mid;
    Deep *deep;

    mid = self->field_10;
    deep = mid->field_2BC;
    return deep->field_1FC;
}
