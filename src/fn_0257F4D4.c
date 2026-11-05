#include "block.h"

/* 0x0257F4D4 .. 0x0257F514, 17 instructions, 68 bytes. */

typedef struct { u8 pad0[0x1A5C]; u8 field_1A5C; } Obj;
extern s32 func_0257C62C(Obj *self);
void func_0257F4D4(Obj *self) {
    if (self->field_1A5C != 0) {
        func_0257C62C(self);
        self->field_1A5C = 0;
    }
}
