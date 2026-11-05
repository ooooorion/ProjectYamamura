#include "block.h"

/* 0x0238AD38 .. 0x0238AD9C, 26 instructions, 104 bytes.
   Tests the +0xB8 object and dispatches the +0x1788 helper. */

extern void func_02090BA8(void);
extern s32 func_02091BC8(s32 self, void *other);
extern void func_0238FD80(void *self, s32 arg1);
s32 func_0238AD38(s32 self) {
    func_02090BA8();
    if (func_02091BC8(self, (u8 *)self + 0xB8) != 0) {
        func_0238FD80((void *)(self + 0x1788), 0x1B);
        return 1;
    }
    return 0;
}
