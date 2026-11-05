#include "block.h"

/* 0x022023AC .. 0x022023F4, 19 instructions, 76 bytes.
   Resolves the middle value through a helper before forwarding all three. */

extern s32 func_0211BCC0(s32 value);
extern void func_0220224C(s32 arg0, s32 arg1, s32 arg2);

void func_022023AC(s32 arg0, s32 arg1, s32 arg2) {
    func_0220224C(arg0, func_0211BCC0(arg1), arg2);
}
