#include "block.h"

/* 0x02507F04 .. 0x02507F38, 14 instructions, 56 bytes.
   Releases both stored subresources. */

typedef struct { u8 pad0[0x9C]; s32 field_9C; u8 padA0[0x1C]; s32 field_BC; } Obj;
extern void func_0246CE80(s32 value);
extern void func_02472240(s32 value);
void func_02507F04(Obj *self) {
    func_0246CE80(self->field_9C);
    func_02472240(self->field_BC);
}
