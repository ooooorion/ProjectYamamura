#include "block.h"

/* 0x023A3FB8 .. 0x023A3FE0, 11 instructions, 44 bytes.
   Runs two teardown helpers. */

extern void func_0205AE28(s32 address);
extern void func_02057740(s32 value);
void func_023A3FB8(s32 self) {
    func_0205AE28(self + 0x2C);
    func_02057740(0);
}
