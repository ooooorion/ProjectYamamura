#include "block.h"

/* 0x021FF258 .. 0x021FF2CC, 30 instructions, 120 bytes.
   When the object is idle and the +0x7C countdown is nonzero, either clears
   the countdown on a successful check or decrements it. */

typedef struct {
    u8 pad0[0x18];
    s32 field_18;
    u8 pad1C[0x60];
    s32 field_7C;
} Obj;

extern s32 func_021FF1EC(Obj *self);

void func_021FF258(Obj *self) {
    if (self->field_18 == 0 && self->field_7C != 0) {
        if (func_021FF1EC(self) == 0) {
            self->field_7C = 0;
            return;
        }
        self->field_7C = self->field_7C - 1;
    }
}
