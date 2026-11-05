#include "block.h"

/* 0x02561378 .. 0x025613B8, 17 instructions, 68 bytes. */

typedef struct { u8 pad0[0x1F]; u8 field_1F; } Obj;
extern s32 func_02091AD0(void);
extern s32 func_0256133C(Obj *self);
void func_02561378(Obj *self) {
    if (func_02091AD0() != 0) {
        func_0256133C(self);
        self->field_1F = 1;
    }
}
