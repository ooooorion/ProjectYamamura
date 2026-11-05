#include "block.h"

/* 0x024D8A30 .. 0x024D8AC0, 37 instructions, 148 bytes.
   Creates the inner resource, dispatches its +0x14 method and registers three values. */

typedef struct {
    u8 pad0[0x1D4];
    void *field_1D4;
    u8 pad1D8[8];
    s32 field_1E0;
    u8 pad1E4[8];
    s32 field_1EC;
    s32 field_1F0;
} Obj;
extern void *func_026E98B4(s32 arg0, s32 arg1, s32 arg2);
extern void func_0275A934(s32 value, s32 arg1);
extern void func_0275A93C(void *self, s32 value);
void func_024D8A30(Obj *self, s32 *arg1) {
    void *object;

    object = func_026E98B4(0, *arg1, 3);
    self->field_1D4 = object;
    (*(void (**)(void))((u8 *)*(void **)((u8 *)object + 0x20) + 0x14))();
    func_0275A934(self->field_1EC, 1);
    func_0275A934(self->field_1F0, 1);
    func_0275A934(self->field_1E0, 1);
    func_0275A93C(self->field_1D4, self->field_1EC);
    func_0275A93C(self->field_1D4, self->field_1F0);
    func_0275A93C(self->field_1D4, self->field_1E0);
}
