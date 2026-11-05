#include "block.h"

/* 0x02010A14 .. 0x02010A20, 4 instructions, 16 bytes.
   lwz + cntlzw + srwi is GHS's "equals zero" idiom. There is no closing
   clrlwi, so the return is 32-bit rather than u8. */

typedef struct {
    u8 pad0[360];
    u32 field_360;
} Obj;

u32 func_02010A14(Obj *self) {
    return self->field_360 == 0;
}
