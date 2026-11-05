#include "block.h"

/* 0x0211A1CC .. 0x0211A1D4, 3 instructions, 12 bytes.
   Clears the byte at +0x258. */

typedef struct {
    u8 pad0[0x258];
    u8 field_258;
} Obj;

void func_0211A1CC(Obj *self) {
    self->field_258 = 0;
}
