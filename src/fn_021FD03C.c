#include "block.h"

/* 0x021FD03C .. 0x021FD094, 23 instructions, 92 bytes.
   Uses the supplied block or allocates eight bytes, then stores both input
   words into it. */

extern void *func_0276FB54(s32 size);

void func_021FD03C(void *arg0, s32 *arg1, s32 *arg2) {
    void *block;

    block = arg0;
    if ((block != 0) || (block = func_0276FB54(8), ((block == 0) == 0))) {
        ((s32 *)block)[0] = *arg1;
        ((s32 *)block)[1] = *arg2;
    }
}
