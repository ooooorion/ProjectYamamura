#include "block.h"

/* 0x0243C8E8 .. 0x0243C934, 20 instructions, 80 bytes.
   Rejects a matching identifier, otherwise dispatches vtable slot 9. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(void);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; u32 field_C; };
s32 func_0243C8E8(Obj *self, u32 arg1) {
    if (arg1 == self->field_C) return 0;
    self->vtable[9]();
    return 1;
}
