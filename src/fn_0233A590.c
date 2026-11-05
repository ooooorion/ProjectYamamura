#include "block.h"

/* 0x0233A590 .. 0x0233A5C0, 13 instructions, 52 bytes.
   Runs two setup helpers. */

extern void func_0233A4D4(void);
extern void func_0233A538(s32 arg0);
void func_0233A590(s32 arg0) { func_0233A4D4(); func_0233A538(arg0); }
