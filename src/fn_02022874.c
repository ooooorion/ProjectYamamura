#include "block.h"

/* 0x02022874 .. 0x02022884, 5 instructions, 20 bytes.
   Equality against 5 at +0x180, immediately after func_02022860. */

typedef struct {
    u8 pad0[384];
    u32 field_384;
} Obj;

u32 func_02022874(Obj *self) {
    return self->field_384 == 5;
}
