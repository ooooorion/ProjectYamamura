#include "block.h"

/* 0x02456050 .. 0x024560A8, 23 instructions, 92 bytes.
   Validates the stored resource and updates the active flag. */

typedef struct { u8 pad0[0x20]; s32 field_20; u8 pad24[0x1C2A]; s8 field_1C4E; } Obj;
extern void func_0276226C(s32 value);
extern s32 func_027625A8(s32 value, s32 mask);
void func_02456050(Obj *self) {
    if (func_027625A8(self->field_20, 0xFFFF) != 0) {
        func_0276226C(self->field_20);
        self->field_1C4E = 1;
        return;
    }
    self->field_1C4E = 0;
}
