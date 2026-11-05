#include "block.h"

/* 0x02507F74 .. 0x02507FA8, 14 instructions, 56 bytes.
   Releases both stored subresources. */

typedef struct { u8 pad0[0xB8]; s32 field_B8; s32 field_BC; } Obj;
extern void func_0247A134(s32 value);
extern void func_02472B4C(s32 value);
void func_02507F74(Obj *self) {
    func_0247A134(self->field_B8);
    func_02472B4C(self->field_BC);
}
