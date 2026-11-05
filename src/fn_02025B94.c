#include "block.h"

/* 0x02025B94 .. 0x02025BA0, 4 instructions, 16 bytes.
   Null test on the word at +0x0C. */

typedef struct {
    u8 pad0[12];
    u32 field_12;
} Obj;

u32 func_02025B94(Obj *self) {
    return self->field_12 == 0;
}
