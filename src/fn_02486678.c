#include "block.h"

/* 0x02486678 .. 0x02486684, 4 instructions, 16 bytes.
   Returns the shared global field at +0x190. */

s32 func_02486678(void) {
    return *(s32 *)((u8 *)*(void **)0x10189468 + 0x190);
}
