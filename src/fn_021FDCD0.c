#include "block.h"

/* 0x021FDCD0 .. 0x021FDD30, 25 instructions, 100 bytes.
   Clears the supplied or freshly allocated word, then copies the small byte
   from the first argument into the second. */

extern void *func_0276FB54(s32 size);

void func_021FDCD0(u8 *arg0, s32 *arg1) {
    s32 *block;
    u8 value;

    block = arg1;
    if ((arg1 != 0) || (block = func_0276FB54(4), ((block == 0) == 0))) {
        *block = -1;
    }
    value = *arg0;
    if (value < 0xE) {
        *arg1 = value;
    }
}
