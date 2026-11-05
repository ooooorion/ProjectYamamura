#include "block.h"

/* 0x0217F454 .. 0x0217F478, 10 instructions, 40 bytes.
   Calls func_0211BCC8 with the incoming r3 and sign-extends the byte at
   +0x21 of the returned pointer. */

extern void *func_0211BCC8(void);

s8 func_0217F454(void) {
    return *(s8 *)((u8 *)func_0211BCC8() + 0x21);
}
