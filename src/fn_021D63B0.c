#include "block.h"

/* 0x021D63B0 .. 0x021D6400, 21 instructions, 84 bytes.
   Marks +0x560, optionally writes a local state through the first helper,
   then releases the handle at +0x53C. */

typedef struct {
    u8 pad0[0x53C];
    s32 field_53C;
    u8 pad540[0x20];
    u8 field_560;
} Obj;

extern void func_021D61B0(Obj *self, s32 *value);
extern void func_025E5FC0(s32 value);

void func_021D63B0(Obj *self, s32 arg1) {
    s32 value;

    self->field_560 = 1;
    if (arg1 != 0) {
        value = 0;
        func_021D61B0(self, &value);
    }
    func_025E5FC0(self->field_53C);
}
