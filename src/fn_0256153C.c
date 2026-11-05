#include "block.h"

/* 0x0256153C .. 0x025615A0, 26 instructions, 104 bytes. */

extern s32 func_02090BA8(void);
extern s32 func_02091BC8(s32 value, s32 arg1);
extern s32 func_0253B888(s32 value, s32 arg1);
s32 func_0256153C(s32 arg0) {
    func_02090BA8();
    if (func_02091BC8(arg0, arg0 + 0xB8) != 0) {
        func_0253B888(arg0 + 0x1958, 0x11);
        return 1;
    }
    return 0;
}
