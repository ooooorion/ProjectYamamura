#include "block.h"

/* 0x02344784 .. 0x023447B8, 14 instructions, 56 bytes.
   Releases two adjacent subobjects. */

extern void func_02770584(s32 arg0);
void func_02344784(s32 self) {
    func_02770584(self + 0x18);
    func_02770584(self + 0x2C);
}
