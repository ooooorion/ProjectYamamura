#include "block.h"

/* 0x020BCC0C .. 0x020BCC34, 11 instructions, 44 bytes.
   Same state-2 selector as 0x020BCBB4, returning the argument advanced by
   0x130 when the state is not 2. */

typedef struct {
    u8 pad0[0x20];
    s32 state_20;
} Manager;

typedef struct {
    u8 pad0[0x14];
    s32 field_14;
} Shared;

s32 func_020BCC0C(s32 value) {
    if (((Manager *)*(void **)0x10189448)->state_20 != 2) {
        return value + 0x130;
    }
    return ((Shared *)*(void **)0x1018B54C)->field_14;
}
