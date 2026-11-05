#include "block.h"

/* 0x02388594 .. 0x023885FC, 27 instructions, 108 bytes.
   Tests the +0x20 nibble and the +0x1650 state. */

extern s32 func_0253D650(void *self, void *other);
extern void func_0253D440(void *self);
s32 func_02388594(void *self) {
    if (!((*(u32 *)((u8 *)self + 0x20) >> 4) & 0xF) &&
        (func_0253D650(self, (u8 *)self + 0x1650) & 4)) {
        func_0253D440(self);
        return 1;
    }
    return 0;
}
