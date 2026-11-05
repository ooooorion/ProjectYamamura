#include "block.h"

/* 0x0233A5C4 .. 0x0233A5FC, 15 instructions, 60 bytes.
   Conditionally refreshes the byte at +0x38. */

extern s32 func_0267E934(void);
extern s8 func_0267F1F4(void);
void func_0233A5C4(void *self) {
    if (func_0267E934() != 0) *(s8 *)((u8 *)self + 0x38) = func_0267F1F4();
}
