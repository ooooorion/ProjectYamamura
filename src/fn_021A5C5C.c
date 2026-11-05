#include "block.h"

/* 0x021A5C5C .. 0x021A5C9C, 17 instructions, 68 bytes.
   When the subsystem query returns zero, runs the object setup helper and
   marks +0x50B. */

typedef struct {
    u8 pad0[0x50B];
    u8 field_50B;
} Obj;

extern s32 func_02131894(void);
extern void func_021A5AF8(Obj *self);

void func_021A5C5C(Obj *self) {
    if (func_02131894() == 0) {
        func_021A5AF8(self);
        self->field_50B = 1;
    }
}
