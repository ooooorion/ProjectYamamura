#include "block.h"

/* 0x0250E454 .. 0x0250E488, 14 instructions, 56 bytes.
   Runs both shared updates on +0xA8. */

typedef struct { u8 pad0[0xA8]; s32 field_A8; } Obj;
extern void func_024750EC(s32 value);
extern void func_024751F0(s32 value);
void func_0250E454(Obj *self) {
    func_024750EC(self->field_A8);
    func_024751F0(self->field_A8);
}
