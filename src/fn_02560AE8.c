#include "block.h"

/* 0x02560AE8 .. 0x02560AF8, 5 instructions, 20 bytes. */

typedef struct {
    u8 pad0[0x34C];
    u8 *field_34C;
    u8 pad350[0x15EC];
    s32 field_193C;
} Obj;
void func_02560AE8(Obj *self) {
    self->field_34C = (u8 *)self + 0x1930;
    self->field_193C = 2;
}
