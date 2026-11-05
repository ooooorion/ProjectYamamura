#include "block.h"

/* 0x0222E708 .. 0x0222E760, 22 instructions, 88 bytes.
   Sets the +0x70 flag bit when the shared predicate succeeds. */

typedef struct Obj Obj;
struct Obj {
    u8 pad0[0x70];
    s32 field_70;
};

extern s32 func_0222E3A0(void);

s32 func_0222E708(Obj *self) {
    if (func_0222E3A0() != 0) {
        self->field_70 |= 4;
        return 1;
    }
    return 0;
}
