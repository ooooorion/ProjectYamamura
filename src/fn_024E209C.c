#include "block.h"

/* 0x024E209C .. 0x024E20AC, 5 instructions, 20 bytes.
   True when the provided state is five. */

s32 func_024E209C(s32 *value) {
    return (*value ^ 5) == 0;
}
