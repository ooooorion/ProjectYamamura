#include "block.h"

/* 0x020BCBE0 .. 0x020BCC08, 11 instructions, 44 bytes.
   Same state-2 selector as 0x020BCBB4, returning the argument advanced by
   0xAC when the state is not 2. */

typedef struct {
    u8 pad0[0x20];
    s32 state_20;
} Manager;

typedef struct {
    u8 pad0[0x14];
    s32 field_14;
} Shared;

s32 func_020BCBE0(s32 value) {
    if (((Manager *)*(void **)0x10189448)->state_20 != 2) {
        return value + 0xAC;
    }
    return ((Shared *)*(void **)0x1018B54C)->field_14;
}
