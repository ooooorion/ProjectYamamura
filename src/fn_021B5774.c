#include "block.h"

/* 0x021B5774 .. 0x021B57C8, 22 instructions, 88 bytes.
   When either +0x60 or +0x64 of the second object is set, releases the
   embedded block at this object's +0x2C offset and decrements +0x28. */

typedef struct {
    u8 pad0[0x28];
    s32 field_28;
    s32 field_2C;
} Obj;

typedef struct {
    u8 pad0[0x60];
    s32 field_60;
    s32 field_64;
} Other;

extern void func_0276FFCC(void *block);

void func_021B5774(Obj *self, Other *other) {
    if (other->field_64 != 0 || other->field_60 != 0) {
        func_0276FFCC((u8 *)other + self->field_2C);
        self->field_28 = self->field_28 - 1;
    }
}
