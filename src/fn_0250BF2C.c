#include "block.h"

/* 0x0250BF2C .. 0x0250BF60, 14 instructions, 56 bytes.
   Runs both shared updates on +0x7C. */

typedef struct { u8 pad0[0x7C]; s32 field_7C; } Obj;
extern void func_02464768(s32 value);
extern void func_024648E4(s32 value);
void func_0250BF2C(Obj *self) {
    func_02464768(self->field_7C);
    func_024648E4(self->field_7C);
}
