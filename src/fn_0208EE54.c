#include "block.h"

/* 0x0208EE54 .. 0x0208EE6C, 7 instructions, 28 bytes.
   Decrement that saturates at zero: the load is kept in a local and the
   store only happens when the old value was non-zero. The decremented value
   is what the function returns. */

s32 func_0208EE54(s32 *value) {
    s32 current;

    current = *value;
    if (current != 0) {
        current -= 1;
        *value = current;
    }
    return current;
}
