#include "block.h"

/* 0x024BF468 .. 0x024BF4B8, 21 instructions, 84 bytes.
   Dispatches the active vtable method and posts event 4. */

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
void func_024BF468(Obj *self) {
    if (self->field_118 & 2) {
        self->vtable[35](self);
    }
    func_024C01A8(&self->field_1DC, 4);
}
