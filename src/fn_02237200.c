#include "block.h"

/* 0x02237200 .. 0x02237250, 21 instructions, 84 bytes.
   Refreshes the shared state, then invokes two slots on the object at +0x0C. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[0xC];
    ObjMethod *vtable;
};

extern void func_02236CD4(void);

void func_02237200(Obj *self) {
    func_02236CD4();
    self->vtable[45](self);
    self->vtable[47](self);
}
