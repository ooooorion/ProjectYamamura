#include "block.h"

/* 0x02030854 .. 0x02030860, 4 instructions, 16 bytes.
   lwz + cntlzw + srwi is the zero test at +0x178. */

typedef struct {
    u8 pad0[0x178];
    s32 field_178;
} Obj;

s32 func_02030854(Obj *self) {
    return self->field_178 == 0;
}
