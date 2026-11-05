#include "block.h"

/* 0x02023C64 .. 0x02023C70, 4 instructions, 16 bytes.
   Null test at +0x180. */

typedef struct {
    u8 pad0[384];
    u32 field_384;
} Obj;

u32 func_02023C64(Obj *self) {
    return self->field_384 == 0;
}
