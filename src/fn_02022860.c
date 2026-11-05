#include "block.h"

/* 0x02022860 .. 0x02022870, 5 instructions, 20 bytes.
   Equality against 4 at +0x180. */

typedef struct {
    u8 pad0[384];
    u32 field_384;
} Obj;

u32 func_02022860(Obj *self) {
    return self->field_384 == 4;
}
