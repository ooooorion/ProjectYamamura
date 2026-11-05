#include "block.h"

/* 0x02187690 .. 0x021876B8, 11 instructions, 44 bytes.
   True when the second argument exists and its +0x08 pointer dereferences
   to the same word as this object's +0x540 field. Both loads happen before
   the compare, so the pointed-to word is read only once. */

typedef struct {
    u8 pad0[0x540];
    u32 field_540;
} Obj;

typedef struct {
    u8 pad0[8];
    u32 *field_8;
} Other;

s32 func_02187690(Obj *self, Other *other) {
    if (other != 0 && self->field_540 == *other->field_8) {
        return 1;
    }
    return 0;
}
