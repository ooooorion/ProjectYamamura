#include "block.h"

/* 0x023F01FC .. 0x023F0268, 28 instructions, 112 bytes.
   Combines the readiness checks and updates the cached flag. */

typedef struct { u8 pad0[0x528]; s32 field_528; u8 pad52C[0x16F]; u8 field_69B; } Obj;
extern s32 func_023EFDA4(void);
extern s32 func_023EFF4C(Obj *self, s32 value);
extern void func_023F01D4(Obj *self, s32 value);
void func_023F01FC(Obj *self) {
    s32 result;
    result = 1;
    if (func_023EFDA4() == 0 || (self->field_69B == 0 && func_023EFF4C(self, self->field_528) != 0)) result = 0;
    func_023F01D4(self, result);
}
