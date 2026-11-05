#include "block.h"

/* 0x0217DA20 .. 0x0217DA6C, 20 instructions, 80 bytes.
   Releases five consecutive handle fields in ascending order. */

typedef struct {
    u8 pad0[0x518];
    s32 field_518;
    s32 field_51C;
    s32 field_520;
    s32 field_524;
    s32 field_528;
} Obj;

extern void func_026C8E48(s32 handle);

void func_0217DA20(Obj *self) {
    func_026C8E48(self->field_518);
    func_026C8E48(self->field_51C);
    func_026C8E48(self->field_520);
    func_026C8E48(self->field_524);
    func_026C8E48(self->field_528);
}
