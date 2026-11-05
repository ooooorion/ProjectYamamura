#include "block.h"

/* 0x0247EA28 .. 0x0247EA38, 5 instructions, 20 bytes.
   Returns the shared global field at +0x8F90. */

s32 func_0247EA28(void) {
    return *(s32 *)((u8 *)*(void **)0x10188EB8 + 0x8F90);
}
