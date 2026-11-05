#include "block.h"

/* 0x024866E8 .. 0x024866F4, 4 instructions, 16 bytes.
   Returns the shared global byte at +0xC39. */

u8 func_024866E8(void) {
    return *(u8 *)((u8 *)*(void **)0x10189468 + 0xC39);
}
