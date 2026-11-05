#include "block.h"

/* 0x02035890 .. 0x0203589C, 4 instructions, 16 bytes.
   Store the argument at +0xBC, then set the byte at +0xCA. */

typedef struct {
    u8 pad0[0xBC];
    s32 field_BC;
    u8 pad_C0[0x0A];
    u8 flag_CA;
} Obj;

void func_02035890(Obj *self, s32 value) {
    self->field_BC = value;
    self->flag_CA = 1;
}
