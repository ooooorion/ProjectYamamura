#include "block.h"

/* 0x021FD6E0 .. 0x021FD6F8, 7 instructions, 28 bytes.
   Maps the -1 sentinel to 0xFF. */

void func_021FD6E0(s8 *output, s32 *input) {
    s32 value = *input;
    s32 result = 0xFF;
    if (value != -1) result = value;
    *output = (s8)result;
}
