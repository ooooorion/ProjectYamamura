#include "block.h"

/* 0x0256D5E0 .. 0x0256D644, 26 instructions, 104 bytes. */

typedef struct { u8 pad0[0x1684]; s32 field_1684; } Obj;
extern s32 func_02091AD0(Obj *self);
extern s32 func_0256D3C4(Obj *self);
s32 func_0256D5E0(Obj *self) {
    if (self->field_1684 == 3 && func_02091AD0(self) != 0) {
        func_0256D3C4(self);
        return 1;
    }
    return 0;
}
