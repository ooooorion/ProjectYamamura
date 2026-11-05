#include "block.h"

/* 0x02507FE4 .. 0x02508018, 14 instructions, 56 bytes.
   Releases both stored subresources. */

typedef struct { u8 pad0[0xB8]; s32 field_B8; s32 field_BC; } Obj;
extern void func_0247A144(s32 value);
extern void func_02472BEC(s32 value);
void func_02507FE4(Obj *self) {
    func_0247A144(self->field_B8);
    func_02472BEC(self->field_BC);
}
