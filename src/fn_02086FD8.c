#include "block.h"

/* 0x02086FD8 .. 0x02086FDC, 2 instructions, 8 bytes.
   Constant accessor returning 6 MiB; see 0x02086FD0. */

s32 func_02086FD8(void) {
    return 0x600000;
}
