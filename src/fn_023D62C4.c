#include "block.h"

/* 0x023D62C4 .. 0x023D633C, 31 instructions, 124 bytes.
   Either dispatches the virtual handler or records the pending value. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { ObjMethod *vtable; };
extern void func_023D62BC(Obj *self, s32 arg1);
extern void func_02055620(void *ptr, s32 value);
void func_023D62C4(Obj *self, s32 arg1) {
    if (*(s32 *)((u8 *)self + 0x118) & 2) {
        func_023D62BC(self, arg1);
        (*(void (**)(Obj *))((u8 *)self->vtable + 0x8C))(self);
        return;
    }
    *(s32 *)((u8 *)self + 0x28C) = arg1;
    func_02055620((u8 *)self + 0x228, 8);
}
