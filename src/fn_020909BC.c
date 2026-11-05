#include "block.h"

/* 0x020909BC .. 0x020909C0, 2 instructions, 8 bytes.
   Constant accessor returning 1; 0x020909D4 repeats it. */

s32 func_020909BC(void) {
    return 1;
}
