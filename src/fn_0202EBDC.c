#include "block.h"

/* 0x0202EBDC .. 0x0202EBEC, 5 instructions, 20 bytes.
   Equality against 3 at +0x178, the same idiom as func_02021C48. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
} Obj;

u32 func_0202EBDC(Obj *self) {
    return self->field_376 == 3;
}
