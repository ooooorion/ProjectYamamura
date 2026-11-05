#include "block.h"

/* Near miss, not matched and not listed in src/functions.tsv.
   Target: 0x02B8AE48..0x02B8AEC8 (132 bytes, 33 instructions).
   The guard/table relocations resolve, but GHS produces a pointer walk at
   -O2 and different loop/register shapes at -O1/-O1 -Onocse. */

typedef void (*InitFn)(void);

extern u32 __init_guard;
extern InitFn __init_array[];

void __init(void) {
    u32 i;

    if (__init_guard) return;
    __init_guard = 1;

    for (i = 0; __init_array[i] != 0; i++) {
        __init_array[i]();
    }
}
