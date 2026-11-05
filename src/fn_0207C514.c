#include "block.h"

/* 0x0207C514 .. 0x0207C518, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 8. The identical body appears
   at 0x0207C54C and 0x0207C9E0/0x0207C9E8. */

s32 func_0207C514(s32 value) {
    return value + 8;
}
