#include "block.h"

/* 0x0222AC9C .. 0x0222ACDC, 16 instructions, 64 bytes.
   Recomputes one field from the two adjacent counters. */

typedef struct Obj Obj;
struct Obj {
    u8 pad0[0x54];
    s32 field_54;
    u8 pad58[0xC];
    s32 field_64;
    s32 field_68;
};

extern s32 func_026D1614(s32 a, s32 b);

void func_0222AC9C(Obj *self) {
    self->field_54 = func_026D1614(self->field_64 + 1, self->field_68 + 1);
}
