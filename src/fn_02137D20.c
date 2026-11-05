#include "block.h"

/* 0x02137D20 .. 0x02137D24, 2 instructions, 8 bytes.
   Stores a word at +0x80. */

typedef struct {
    u8 pad0[0x80];
    s32 field_80;
} Obj;

void func_02137D20(Obj *self, s32 value) {
    self->field_80 = value;
}
