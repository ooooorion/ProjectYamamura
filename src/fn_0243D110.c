#include "block.h"

/* 0x0243D110 .. 0x0243D1D4, 50 instructions, 200 bytes.
   Handles the inactive and active paths of the object state machine. */

typedef struct {
    u8 pad0[0x118]; s32 field_118;
    u8 pad11C[0xF8]; s32 field_214;
    u8 pad218[0x4C]; s32 field_264; s32 field_268; s32 field_26C; s32 field_270;
    u8 pad274[0x30]; s8 field_2A4;
    u8 pad2A5[0x76B]; s32 field_A10;
} Obj;
extern void func_0243CD38(Obj *self);
extern void func_0243CDB0(Obj *self);
extern void func_0243D0A0(Obj *self);
extern void func_02760068(s32 value, s32 flag);
s32 func_0243D110(Obj *self, s8 arg1) {
    if (!(self->field_118 & 2)) {
        if (self->field_A10 == 3) {
            func_0243CD38(self);
            self->field_118 = self->field_118 | 1;
            func_0243CDB0(self);
        }
        return 0;
    }
    self->field_2A4 = arg1;
    func_0243D0A0(self);
    func_0243CD38(self);
    func_02760068(self->field_264, 1);
    func_02760068(self->field_268, 1);
    func_02760068(self->field_214, 1);
    func_02760068(self->field_26C, 0);
    func_02760068(self->field_270, 0);
    return 1;
}
