#include "block.h"

/* 0x0241D1F0 .. 0x0241D238, 19 instructions, 76 bytes.
   Clears the active marker and releases the stored resource. */

typedef struct { u8 pad0[0x2BE4]; s32 field_2BE4; u8 pad2BE8[0x88]; s8 field_2C70; } Obj;
extern void func_02041E18(s32 value);
extern void func_0241D0B0(void *self, s32 arg1);
void func_0241D1F0(Obj *self) {
    self->field_2C70 = 0;
    func_02041E18(self->field_2BE4);
    func_0241D0B0(self, 0);
}
