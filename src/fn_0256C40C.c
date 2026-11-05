#include "block.h"

/* 0x0256C40C .. 0x0256C440, 14 instructions, 56 bytes. */

typedef struct { u8 pad0[0x13C4]; u32 field_13C4; } Obj;
extern void *func_0208FFF4(void);
void func_0256C40C(Obj *self) {
    *(u32 *)((u8 *)func_0208FFF4() + 0xE4) = self->field_13C4 >> 0x1B;
}
