#include "block.h"

/* 0x02490750 .. 0x02490754, 2 instructions, 8 bytes.
   Returns the address eight bytes into +0x1F0. */

s32 func_02490750(s32 arg0) {
    return arg0 + 0x1F8;
}
