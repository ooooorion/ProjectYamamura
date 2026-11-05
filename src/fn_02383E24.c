#include "block.h"

/* 0x02383E24 .. 0x02383E74, 21 instructions, 84 bytes.
   Forwards through the object with id 9. */

extern void *func_02758940(s32 id);
extern void func_028B94E8(s32 arg0, s32 arg1, s32 arg2);
void func_02383E24(s32 arg0, s32 arg1) {
    void *object = func_02758940(9);
    if (object != 0) func_028B94E8(arg0, arg1, *(s32 *)((u8 *)object + 0x9DC));
}
