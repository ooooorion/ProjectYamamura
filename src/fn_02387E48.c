#include "block.h"

/* 0x02387E48 .. 0x02387E94, 20 instructions, 80 bytes.
   Releases the +4 handle when active. */

extern s32 func_026C99C0(s32 value);
extern void func_026C99AC(s32 value, s32 flag);
extern void func_026C99D8(s32 value, s32 flag);
void func_02387E48(void *self) {
    if (func_026C99C0(*(s32 *)((u8 *)self + 4)) != 0) {
        func_026C99AC(*(s32 *)((u8 *)self + 4), 0);
        func_026C99D8(*(s32 *)((u8 *)self + 4), 0);
    }
}
