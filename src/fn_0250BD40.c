#include "block.h"

/* 0x0250BD40 .. 0x0250BDC0, 33 instructions, 132 bytes.
   Applies the four state values and runs the shared update. */

typedef struct { u8 pad0[0xA4]; s32 field_A4; } Obj;
extern void func_02469898(s32 value, s32 arg1);
extern void func_024698BC(s32 value, s32 arg1);
extern void func_024698C4(s32 value, s32 arg1);
extern void func_024698CC(s32 value, s32 arg1);
extern void func_0246A360(s32 value);
void func_0250BD40(Obj *self, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_024698BC(self->field_A4, arg2);
    func_02469898(self->field_A4, arg3);
    func_024698C4(self->field_A4, arg4);
    func_024698CC(self->field_A4, *arg1);
    func_0246A360(self->field_A4);
}
