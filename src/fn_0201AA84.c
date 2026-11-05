#include "block.h"

/* 0x0201AA84 .. 0x0201AA94, 5 instructions, 20 bytes.
   xori + cntlzw + srwi is the equality form of the same 32-bit idiom used by
   func_02010A14: the field is compared against 2, not tested for zero. */

typedef struct {
    u8 pad0[488];
    u32 field_488;
} Obj;

u32 func_0201AA84(Obj *self) {
    return self->field_488 == 2;
}
