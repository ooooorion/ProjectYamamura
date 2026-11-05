#include "block.h"

/* 0x023923E8 .. 0x02392420, 15 instructions, 60 bytes.
   Clears +0x10 on the supplied or newly allocated object. */

extern void *func_0276FB54(s32 size);
void func_023923E8(void *self) {
    void *object = self;
    if (object != 0 || (object = func_0276FB54(0x14), object != 0)) {
        *(s32 *)((u8 *)object + 0x10) = 0;
    }
}
