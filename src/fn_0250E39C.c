#include "block.h"

/* 0x0250E39C .. 0x0250E3E8, 20 instructions, 80 bytes.
   Runs the three +0xA8 updates; the middle argument is in r5. */

typedef struct { u8 pad0[0xA8]; s32 field_A8; } Obj;
extern s32 func_024750A8(s32 value);
extern s32 func_024750EC(s32 value);
extern s32 func_024750F4(s32 value, s32 arg);
void func_0250E39C(Obj *self, s32 arg1, s32 arg2) {
    func_024750EC(self->field_A8);
    func_024750F4(self->field_A8, arg2);
    func_024750A8(self->field_A8);
}
