#include "block.h"

/* 0x02419034 .. 0x0241907C, 19 instructions, 76 bytes.
   Runs the stored resource cleanup with code 2 when idle. */

typedef struct { u8 pad0[0x328C]; s32 field_328C; u8 pad3290[8]; u8 field_3298; } Obj;
extern void func_02760068(s32 value, s32 flag);
extern void func_0241A7A4(void *self, s32 arg1);
void func_02419034(Obj *self) {
    if (self->field_3298 == 0) {
        func_02760068(self->field_328C, 1);
        func_0241A7A4((u8 *)self + 0x1DC, 2);
    }
}
