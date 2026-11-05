#include "block.h"

/* 0x0226365C .. 0x022636AC, 21 instructions, 84 bytes.
   Resets one counter, closes the nested +0x674 object when its +0x680 word
   is nonzero, and clears the +0x69C flag. */

typedef struct Sub Sub;
struct Sub {
    u8 pad0[0x680];
    s32 field_680;
};

typedef struct Obj Obj;
struct Obj {
    u8 pad0[0x69C];
    u8 field_69C;
    u8 pad69D[3];
    s32 field_6A0;
    u8 pad6A4[0x18];
    Sub *sub_6BC;
};

extern void func_0226AD58(void *object, s32 flag);

void func_0226365C(Obj *self) {
    Sub *sub = self->sub_6BC;

    self->field_6A0 = 3;
    if (sub->field_680 != 0) {
        func_0226AD58((u8 *)sub + 0x674, 0);
    }
    self->field_69C = 0;
}
