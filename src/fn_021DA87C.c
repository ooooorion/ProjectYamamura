#include "block.h"

/* 0x021DA87C .. 0x021DA8B8, 16 instructions, 64 bytes.
   Releases the +0x4E8 subobject through the shared helper with slot 6, then
   runs the object-only cleanup. */

extern void func_021D832C(s32 arg0, s32 arg1);
extern void func_021D6368(s32 arg0, s32 arg1);

void func_021DA87C(s32 arg0) {
    func_021D832C(arg0 + 0x4E8, 6);
    func_021D6368(arg0, 0);
}
