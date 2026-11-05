#include "block.h"

/* 0x024BB68C .. 0x024BB6DC, 21 instructions, 84 bytes.
   Dispatches the active vtable method and posts event 2. */

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
extern void func_024BBE34(void *self, s32 arg1);
void func_024BB68C(Obj *self) {
    if (self->field_118 & 2) {
        self->vtable[35](self);
    }
    func_024BBE34(&self->field_1DC, 2);
}
