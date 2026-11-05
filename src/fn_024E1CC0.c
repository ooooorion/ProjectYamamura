#include "block.h"

/* 0x024E1CC0 .. 0x024E1CD8, 7 instructions, 28 bytes.
   True when the shared global state is four. */

s32 func_024E1CC0(void) {
    return (*(s32 *)((u8 *)*(void **)0x10189468 + 0x15C) ^ 4) == 0;
}
