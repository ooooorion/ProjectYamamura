#include "block.h"

/* 0x023F65C8 .. 0x023F65DC, 6 instructions, 24 bytes.
   Sets a bit on the shared object at 0x101823E8. */

void func_023F65C8(void) {
    void *object;
    object = *(void **)0x101823E8;
    *(u8 *)((u8 *)object + 0x164) |= 1;
}
