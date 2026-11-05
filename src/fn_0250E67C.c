#include "block.h"

/* 0x0250E67C .. 0x0250E6C8, 20 instructions, 80 bytes.
   Dispatches +0x9C on both nested objects. */

typedef struct { u8 pad0[0xB8]; void **field_B8; void **field_BC; } Obj;
typedef void (*InnerMethod)(void **);
void func_0250E67C(Obj *self) {
    void **object;

    object = self->field_B8;
    (*(InnerMethod *)((u8 *)*object + 0x9C))(object);
    object = self->field_BC;
    (*(InnerMethod *)((u8 *)*object + 0x9C))(object);
}
