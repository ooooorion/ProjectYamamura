/* Reconstructed from the retained .s slice for 0x02BD02DC..0x02BD0304;
   this is a near miss, not a byte-identical match. */
#include "block.h"

u16 *func_02BD02DC(u16 *arg0, u32 arg1) {
    while (*arg0 != arg1) {
        if (*arg0 == 0) {
            return 0;
        }
        arg0++;
    }
    return arg0;
}
