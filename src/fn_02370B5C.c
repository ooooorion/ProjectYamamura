#include "block.h"

/* 0x02370B5C .. 0x02370BD0, 30 instructions, 120 bytes.
   Copies two looked-up objects into the +0x6C slot. */

extern s32 func_027589E0(s32 id);
extern void func_02880CAC(s32 object, s32 value);
void func_02370B5C(s32 self) {
    s32 first = func_027589E0(0xC);
    s32 second = func_027589E0(0x10);
    if (first != 0 && second != 0) {
        func_02880CAC(first, self + 0x6C);
        func_02880CAC(second, self + 0x6C);
    }
}
