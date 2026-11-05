#include "block.h"

/* 0x02560F48 .. 0x02560FB8, 29 instructions, 116 bytes. */

typedef struct { u8 pad0[4]; s32 field_4; u8 pad8[0x16AC]; s32 field_16B4; } Obj;
extern s32 func_0255E98C(Obj *self);
extern s32 func_026C99C0(s32 value);
extern s32 func_026C99D8(s32 value, s32 arg1);
s32 func_02560F48(Obj *self) {
    if (self->field_16B4 & 1) {
        if (func_026C99C0(self->field_4) != 0) func_026C99D8(self->field_4, 0);
        func_0255E98C(self);
        return 1;
    }
    return 0;
}
