#include "block.h"

/* 0x021FBEB4 .. 0x021FBED8, 10 instructions, 40 bytes.
   Calls the accessor and sets byte +1 of the returned pointer. */

extern void *func_021FBEA8(void);

void func_021FBEB4(void) {
    ((u8 *)func_021FBEA8())[1] = 1;
}
