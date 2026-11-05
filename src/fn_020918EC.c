#include "block.h"

/* 0x020918EC .. 0x020918F4, 3 instructions, 12 bytes.
   Stores the two float arguments in reverse field order: first argument at
   +0x1418, second at +0x1414. */

typedef struct {
    u8 pad0[0x1414];
    f32 value_1414;
    f32 value_1418;
} Obj;

void func_020918EC(Obj *self, f32 first, f32 second) {
    self->value_1418 = first;
    self->value_1414 = second;
}
