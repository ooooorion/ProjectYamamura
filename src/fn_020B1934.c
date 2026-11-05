#include "block.h"

/* 0x020B1934 .. 0x020B1964, 13 instructions, 52 bytes.
   Selects one of two float constants from the state word at +0x20 of the
   object published at 0x10189448. States 1 and 2 take 0x10011FE8; everything
   else takes 0x101B9494. */

typedef struct {
    u8 pad0[0x20];
    s32 state_20;
} Manager;

f32 func_020B1934(void) {
    s32 state;

    state = ((Manager *)*(void **)0x10189448)->state_20;
    if (state == 1 || state == 2) {
        return *(f32 *)0x10011FE8;
    }
    return *(f32 *)0x101B9494;
}
