#include "block.h"

/* 0x0213758C .. 0x02137590, 2 instructions, 8 bytes.
   Stores a byte at +0x21. */

typedef struct {
    u8 pad0[0x21];
    s8 field_21;
} Obj;

void func_0213758C(Obj *self, s8 value) {
    self->field_21 = value;
}
