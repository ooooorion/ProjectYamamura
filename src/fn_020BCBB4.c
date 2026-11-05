#include "block.h"

/* 0x020BCBB4 .. 0x020BCBDC, 11 instructions, 44 bytes.
   In state 2 the function reads a shared field at +0x14 of the object at
   0x1018B54C; otherwise it returns the argument advanced by 0x28. The two
   siblings at 0x020BCBE0 and 0x020BCC0C use +0xAC and +0x130. */

typedef struct {
    u8 pad0[0x20];
    s32 state_20;
} Manager;

typedef struct {
    u8 pad0[0x14];
    s32 field_14;
} Shared;

s32 func_020BCBB4(s32 value) {
    if (((Manager *)*(void **)0x10189448)->state_20 != 2) {
        return value + 0x28;
    }
    return ((Shared *)*(void **)0x1018B54C)->field_14;
}
