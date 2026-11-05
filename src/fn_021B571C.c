#include "block.h"

/* 0x021B571C .. 0x021B5770, 22 instructions, 88 bytes.
   When either +0x50 or +0x54 of the second object is set, releases the
   embedded block at this object's +0x1C offset and decrements +0x18. */

typedef struct {
    u8 pad0[0x18];
    s32 field_18;
    s32 field_1C;
} Obj;

typedef struct {
    u8 pad0[0x50];
    s32 field_50;
    s32 field_54;
} Other;

extern void func_0276FFCC(void *block);

void func_021B571C(Obj *self, Other *other) {
    if (other->field_54 != 0 || other->field_50 != 0) {
        func_0276FFCC((u8 *)other + self->field_1C);
        self->field_18 = self->field_18 - 1;
    }
}
