#include "block.h"

/* 0x024BF51C .. 0x024BF574, 23 instructions, 92 bytes.
   Dispatches the active vtable method, marks +0x220 and posts event 6. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj {
    ObjMethod *vtable;
    u8 pad4[0x114];
    s32 field_118;
    u8 pad11C[0xC0];
    u8 field_1DC;
    u8 pad1DD[0x43];
    s8 field_220;
};
extern void func_024C01A8(void *self, s32 arg1);
void func_024BF51C(Obj *self) {
    if (self->field_118 & 2) {
        self->vtable[35](self);
        self->field_220 = 1;
    }
    func_024C01A8(&self->field_1DC, 6);
}
