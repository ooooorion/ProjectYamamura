#include "block.h"

/* 0x0250BF94 .. 0x0250BFCC, 15 instructions, 60 bytes.
   Applies the state value and runs the shared update. */

typedef struct { u8 pad0[0x7C]; s32 field_7C; } Obj;
extern void func_02464770(s32 value, s32 arg1);
extern void func_02465128(s32 value);
void func_0250BF94(Obj *self, s32 *arg1) {
    func_02464770(self->field_7C, *arg1);
    func_02465128(self->field_7C);
}
