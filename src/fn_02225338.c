#include "block.h"

/* 02225338: returns zero when the value already matches +0x0C; otherwise
   dispatches vtable slot 9 and returns one. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(void);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    u32 field_C;
};

s32 func_02225338(Obj *self, u32 arg1) {
    if (arg1 == self->field_C) {
        return 0;
    }
    self->vtable[9]();
    return 1;
}
