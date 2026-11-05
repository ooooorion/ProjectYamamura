#include "block.h"

/* 0x0253D470 .. 0x0253D484, 6 instructions, 24 bytes. */

typedef struct {
    u8 pad0[0x20];
    u32 field_20;
    u8 pad24[0x15D8];
    s32 field_15FC;
    s32 field_1600;
} Obj;
void func_0253D470(Obj *self) {
    u32 value;

    value = self->field_20;
    self->field_15FC = (value >> 4) & 0xF;
    self->field_1600 = value & 1;
}
