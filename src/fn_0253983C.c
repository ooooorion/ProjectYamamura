#include "block.h"

/* 0x0253983C .. 0x02539878, 16 instructions, 64 bytes. */

typedef struct { u8 pad0[0x1B24]; s32 field_1B24; } Obj;
extern s32 func_02539774(Obj *self);
extern s32 func_02543A44(void);
void func_0253983C(Obj *self) {
    func_02543A44();
    if (self->field_1B24 == 2) func_02539774(self);
}
