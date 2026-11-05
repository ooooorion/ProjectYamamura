#include "block.h"

/* 0x0202C758 .. 0x0202C774, 8 instructions, 32 bytes.
   addi + cmplwi is an unsigned range test: field - 12 <= 2, i.e. 12..14.
   The 1/0 materialisation is followed by clrlwi, so the return is u8. A u32
   result variable with an explicit (u8) cast keeps the single exit; a u8
   variable makes GHS branch directly to blr and shrink the function. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
} Obj;

u8 func_0202C758(Obj *self) {
    u32 value = self->field_376 - 12;
    u32 result = 1;
    if (value > 2) result = 0;
    return (u8)result;
}
