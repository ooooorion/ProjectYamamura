#include "block.h"

/* 0x021256D0 .. 0x021256FC, 12 instructions, 48 bytes.
   State test: +0x44C must be non-zero and +0x458 must be 4 or 5. */

typedef struct {
    u8 pad0[0x44C];
    s32 field_44C;
    u8 pad0_450[0x458 - 0x450];
    s32 field_458;
} Obj;

s32 func_021256D0(Obj *self) {
    s32 state;

    if (self->field_44C != 0) {
        state = self->field_458;
        if (state == 4 || state == 5) {
            return 1;
        }
    }
    return 0;
}
