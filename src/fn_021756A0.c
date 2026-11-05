#include "block.h"

/* 0x021756A0 .. 0x021756B4, 6 instructions, 24 bytes.
   Reads the singleton pointer published at 0x10182F98, then tests its
   +0x20 word for non-zero. The addic/subfe pair is the boolean result. */

typedef struct {
    u8 pad0[0x20];
    s32 field_20;
} Obj;

s32 func_021756A0(void) {
    return (*(Obj **)0x10182F98)->field_20 != 0;
}
