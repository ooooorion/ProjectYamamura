#include "block.h"

/* 0x0217877C .. 0x021787B8, 16 instructions, 64 bytes.
   Calls the allocator-like helper with constants 0xD2F0 and 0x1A5E0 and
   stores its result at +0x0C. */

typedef struct {
    u8 pad0[0xC];
    s32 field_C;
} Obj;

extern s32 func_026D1614(s32 arg0, s32 arg1);

void func_0217877C(Obj *self) {
    self->field_C = func_026D1614(0xD2F0, 0x1A5E0);
}
