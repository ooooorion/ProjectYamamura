#include "block.h"

/* 0x023F15F0 .. 0x023F1620, 13 instructions, 52 bytes.
   Runs the shared setup and the per-object cleanup. */

extern void func_023F11DC(void);
extern void func_023F1504(s32 arg0);
void func_023F15F0(s32 arg0) {
    func_023F11DC();
    func_023F1504(arg0);
}
