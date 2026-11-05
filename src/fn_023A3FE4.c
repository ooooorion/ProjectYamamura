#include "block.h"

/* 0x023A3FE4 .. 0x023A401C, 15 instructions, 60 bytes.
   Forwards the +0x40 value and releases the subobject. */

extern void func_0276912C(s32 address, s32 value);
extern void func_0205AD28(s32 address);
void func_023A3FE4(void *self) {
    func_0276912C((s32)self + 0x2C, *(s32 *)((u8 *)self + 0x40));
    func_0205AD28((s32)self + 0x2C);
}
