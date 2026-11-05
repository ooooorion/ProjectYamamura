#include "block.h"

/* 0x020DCD94 .. 0x020DCDAC, 7 instructions, 28 bytes.
   Decrement that saturates at zero: the load stays in a local and the store
   only happens when the old value was non-zero. The decremented value is what
   the function returns; same shape as 0x0208EE54. */

s32 func_020DCD94(s32 *value) {
    s32 current;

    current = *value;
    if (current != 0) {
        current -= 1;
        *value = current;
    }
    return current;
}
