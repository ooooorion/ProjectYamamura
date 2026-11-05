#include "block.h"

/* 0x0253E004 .. 0x0253E030, 12 instructions, 48 bytes. */

typedef struct { u8 pad0[0x1408]; u8 field_1408; u8 field_1409; } Obj;
s32 func_0253E004(Obj *self) {
    u8 value;

    value = self->field_1409;
    if (self->field_1408 != 0) {
        if (value != 0) return 0;
        return 1;
    }
    if (value != 0) return 1;
    return 0;
}
