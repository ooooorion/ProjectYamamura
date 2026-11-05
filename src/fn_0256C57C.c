#include "block.h"

/* 0x0256C57C .. 0x0256C5E8, 28 instructions, 112 bytes. */

extern s32 func_02090BA8(void);
extern s32 func_02091BC8(s32 value, s32 arg1);
extern s32 func_02556EEC(s32 value, s32 arg1);
extern s32 func_0256C460(s32 value);
s32 func_0256C57C(s32 arg0) {
    func_02090BA8();
    if (func_02091BC8(arg0, arg0 + 0xB8) != 0) {
        func_0256C460(arg0);
        func_02556EEC(arg0 + 0x1750, 0xF);
        return 1;
    }
    return 0;
}
