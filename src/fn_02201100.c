#include "block.h"

/* 0x02201100 .. 0x02201138, 15 instructions, 60 bytes.
   Samples the current value and forwards it, by address, with the argument. */

extern s32 func_022010EC(void);
extern void func_022010AC(s32 value, s32 *out);

void func_02201100(s32 arg0) {
    s32 sp8;

    sp8 = func_022010EC();
    func_022010AC(arg0, &sp8);
}
