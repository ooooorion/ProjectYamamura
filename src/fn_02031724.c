#include "block.h"

/* 0x02031724 .. 0x02031730, 4 instructions, 16 bytes.
   The same lwz/cntlzw/srwi zero test as func_02030854, at +0x0C. */

typedef struct {
    u8 pad0[0x0C];
    s32 field_0C;
} Obj;

s32 func_02031724(Obj *self) {
    return self->field_0C == 0;
}
