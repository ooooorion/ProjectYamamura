#include "block.h"

/* 0x02113CC8 .. 0x02113CCC, 2 instructions, 8 bytes.
   Logical right shift that extracts the high half-word. */

u32 func_02113CC8(u32 value) {
    return value >> 16;
}
