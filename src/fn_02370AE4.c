#include "block.h"

/* 0x02370AE4 .. 0x02370B58, 30 instructions, 120 bytes.
   Copies two looked-up objects into the +0x28 slot. */

extern s32 func_027589E0(s32 id);
extern void func_02880CAC(s32 object, s32 value);
void func_02370AE4(s32 self) {
    s32 first = func_027589E0(0x13);
    s32 second = func_027589E0(0x14);
    if (first != 0 && second != 0) {
        func_02880CAC(first, self + 0x28);
        func_02880CAC(second, self + 0x28);
    }
}
