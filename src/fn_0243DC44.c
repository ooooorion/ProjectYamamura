#include "block.h"

/* 0x0243DC44 .. 0x0243DCB0, 28 instructions, 112 bytes.
   Switches an active object to state 6 and updates its stored mode. */

typedef struct {
    u8 pad0[0x118]; s32 field_118;
    u8 pad11C[0xE8]; s32 field_204;
    u8 pad208[0x9D]; s8 field_2A5;
    u8 pad2A6[0x7A6]; s32 field_A4C;
} Obj;
extern void func_0243CD38(Obj *self);
extern void func_0243D0A0(Obj *self);
extern void func_0243D3C0(Obj *self);
extern void func_02760068(s32 value, s32 flag);
void func_0243DC44(Obj *self, s8 arg1) {
    if (self->field_118 & 2) {
        self->field_A4C = 6;
        func_0243D0A0(self);
        func_0243CD38(self);
        func_02760068(self->field_204, 1);
        self->field_2A5 = arg1;
        func_0243D3C0(self);
    }
}
