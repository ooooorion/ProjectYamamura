#include "block.h"

/* 0x020180E8 .. 0x020180F4, 4 instructions, 16 bytes.
   Same 32-bit null-test idiom as func_02010A14, at a different field. */

typedef struct {
    u8 pad0[488];
    u32 field_488;
} Obj;

u32 func_020180E8(Obj *self) {
    return self->field_488 == 0;
}
