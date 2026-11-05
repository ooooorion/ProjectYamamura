#include "block.h"

/* 0x0248EE44 .. 0x0248EE88, 18 instructions, 72 bytes.
   Releases the inner resource and dispatches vtable slot at +0x8C. */

typedef struct { u8 pad0[0x1DC]; void **field_1DC; } Obj;
typedef void (*InnerMethod)(void **);
extern void func_0275E368(void **self, s32 value);
void func_0248EE44(Obj *self) {
    void **object;
    func_0275E368(self->field_1DC, 0);
    object = self->field_1DC;
    (*(InnerMethod *)((u8 *)*object + 0x8C))(object);
}
