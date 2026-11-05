#include "block.h"

/* 0x0224FE7C .. 0x0224FEB4, 15 instructions, 60 bytes.
   Uses the supplied pointer or allocates four bytes, then clears the word. */

extern s32 *func_0276FB54(s32 size);

void func_0224FE7C(s32 *arg0) {
    s32 *p = arg0;

    if (p == 0) {
        p = func_0276FB54(4);
    }
    if (p != 0) {
        *p = 0;
    }
}
