#include "block.h"

/* 0x0250E6DC .. 0x0250E710, 14 instructions, 56 bytes.
   Releases both stored subresources. */

typedef struct { u8 pad0[0xB8]; s32 field_B8; s32 field_BC; } Obj;
extern void func_0247A0DC(s32 value);
extern void func_02472B4C(s32 value);
void func_0250E6DC(Obj *self) {
    func_0247A0DC(self->field_B8);
    func_02472B4C(self->field_BC);
}
