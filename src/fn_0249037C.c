#include "block.h"

/* 0x0249037C .. 0x024903D4, 23 instructions, 92 bytes.
   Marks both active flags and resets the selected state. */

typedef struct {
    u8 pad0[0x100];
    s32 field_100;
    u8 pad104[0xD8];
    s32 field_1DC;
    void *field_1E0;
    s8 field_1E4;
    u8 pad1E5[0x543];
    u8 field_728;
} Obj;
extern void func_0275E368(s32 value, s32 arg1);
extern void func_02492870(void *value, s32 arg1);
void func_0249037C(Obj *self) {
    self->field_1E4 = 1;
    *(s8 *)((u8 *)self->field_1E0 + 4) = 1;
    func_0275E368(self->field_1DC, 1);
    self->field_100 = 0;
    func_02492870(&self->field_728, 1);
}
