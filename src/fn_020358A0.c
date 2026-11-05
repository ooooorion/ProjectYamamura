#include "block.h"

/* 0x020358A0 .. 0x020358AC, 4 instructions, 16 bytes.
   Another lwz/cntlzw/srwi zero test at +0x0C. */

typedef struct {
    u8 pad0[0x0C];
    s32 field_0C;
} Obj;

s32 func_020358A0(Obj *self) {
    return self->field_0C == 0;
}
