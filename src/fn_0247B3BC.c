#include "block.h"

/* 0x0247B3BC .. 0x0247B408, 20 instructions, 80 bytes.
   Forwards the pair to the shared registration and callback helpers. */

extern void func_0276CDFC(s32 arg1, s32 value, s32 arg0);
extern void func_0276001C(s32 arg1, s32 value);
void func_0247B3BC(s32 arg0, s32 arg1) {
    func_0276CDFC(arg1, 0, arg0);
    func_0276001C(arg1, arg0 + 0xA8);
}
