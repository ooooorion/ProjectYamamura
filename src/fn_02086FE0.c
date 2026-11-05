#include "block.h"

/* 0x02086FE0 .. 0x02086FE4, 2 instructions, 8 bytes.
   Constant accessor returning 5 MiB. */

s32 func_02086FE0(void) {
    return 0x500000;
}
