#include "block.h"

/* 0x020B1968 .. 0x020B197C, 6 instructions, 24 bytes.
   True when the state word at +0x20 of the object at 0x10189448 is non-zero. */

typedef struct {
    u8 pad0[0x20];
    s32 state_20;
} Manager;

s32 func_020B1968(void) {
    return ((Manager *)*(void **)0x10189448)->state_20 != 0;
}
