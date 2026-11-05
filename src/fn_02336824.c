#include "block.h"

/* 0x02336824 .. 0x02336854, 13 instructions, 52 bytes.
   Runs two setup helpers. */

extern void func_023367DC(void);
extern void func_0233A590(s32 arg0);
void func_02336824(s32 arg0) { func_023367DC(); func_0233A590(arg0); }
