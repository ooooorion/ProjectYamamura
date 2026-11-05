#include "block.h"

/* 0x02556E00 .. 0x02556E68, 27 instructions, 108 bytes. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
    u8 pad10[0xC];
    u8 field_1C;
    u8 field_1D;
};
extern s32 func_02556D80(Obj *self);
extern s32 func_0276914C(Obj *self);
void func_02556E00(Obj *self) {
    self->field_1D = 0;
    if (self->field_1C != 0 && self->field_C == -1) self->vtable[5](self);
    func_02556D80(self);
    func_0276914C(self);
}
