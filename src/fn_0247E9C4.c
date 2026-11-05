#include "block.h"

/* 0x0247E9C4 .. 0x0247EA24, 25 instructions, 100 bytes.
   Runs the resource teardown and the type-1 follow-up. */

typedef struct { u8 pad0[0x1AC]; s32 field_1AC; u8 pad1B0[0x13CC]; s32 field_157C; } Obj;
extern void func_0205BB44(s32 value, s32 code);
extern void func_02015F70(s32 value);
extern void func_020163D8(s32 value);
extern s32 func_0247E000(Obj *self);
extern void func_0247E24C(Obj *self, s32 arg1, s32 arg2);
void func_0247E9C4(Obj *self) {
    func_0205BB44(self->field_1AC, 0x56);
    func_02015F70(self->field_157C);
    func_020163D8(self->field_157C);
    if (func_0247E000(self) == 1) {
        func_0247E24C(self, 1, 0);
    }
}
