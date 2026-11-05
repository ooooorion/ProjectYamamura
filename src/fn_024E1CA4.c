#include "block.h"

/* 0x024E1CA4 .. 0x024E1CBC, 7 instructions, 28 bytes.
   True when the shared global state is three. */

s32 func_024E1CA4(void) {
    return (*(s32 *)((u8 *)*(void **)0x10189468 + 0x15C) ^ 3) == 0;
}
