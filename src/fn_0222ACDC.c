#include "block.h"

/* 0x0222ACDC .. 0x0222AD1C, 16 instructions, 64 bytes.
   Recomputes one field from the two adjacent counters. */

typedef struct Obj Obj;
struct Obj {
    u8 pad0[0x58];
    s32 field_58;
    u8 pad5C[0x10];
    s32 field_6C;
    s32 field_70;
};

extern s32 func_026D1614(s32 a, s32 b);

void func_0222ACDC(Obj *self) {
    self->field_58 = func_026D1614(self->field_6C + 1, self->field_70 + 1);
}
