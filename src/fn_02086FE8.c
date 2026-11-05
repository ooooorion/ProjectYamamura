#include "block.h"

/* 0x02086FE8 .. 0x02086FEC, 2 instructions, 8 bytes.
   Constant accessor returning 9 MiB. */

s32 func_02086FE8(void) {
    return 0x900000;
}
