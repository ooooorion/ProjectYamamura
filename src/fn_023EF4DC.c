#include "block.h"

/* 0x023EF4DC .. 0x023EF51C, 17 instructions, 68 bytes.
   Releases the two stored resources unless already destroyed. */

typedef struct { u8 pad0[0x5F8]; s32 field_5F8; s32 field_5FC; u8 pad600[0x90]; s32 field_690; } Obj;
extern void func_0241D6B4(s32 value);
extern void func_024190CC(s32 value);
void func_023EF4DC(Obj *self) {
    if (self->field_690 == 0) func_0241D6B4(self->field_5FC);
    func_024190CC(self->field_5F8);
}
