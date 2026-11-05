#include "block.h"

/* 0x0244C964 .. 0x0244C998, 14 instructions, 56 bytes.
   Runs the shared update and forwards the embedded object. */

extern void func_02012904(void);
extern void func_0244D540(s32 self, s32 arg1);
void func_0244C964(s32 arg0) {
    func_02012904();
    func_0244D540(arg0 + 0x1E4, 1);
}
