#include "block.h"

/* 0x02021C48 .. 0x02021C58, 5 instructions, 20 bytes.
   Equality against 3, in the xori + cntlzw + srwi form. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
} Obj;

u32 func_02021C48(Obj *self) {
    return self->field_376 == 3;
}
