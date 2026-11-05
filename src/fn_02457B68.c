#include "block.h"

/* 0x02457B68 .. 0x02457BA0, 15 instructions, 60 bytes.
   Refreshes +0x1C3C when the selector is nonnegative. */

typedef struct { u8 pad0[0x1C3C]; s32 field_1C3C; } Obj;
extern s32 func_02455B20(Obj *self);
void func_02457B68(Obj *self, s32 arg1) {
    if (arg1 >= 0) self->field_1C3C = func_02455B20(self);
}
