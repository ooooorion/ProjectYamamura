#include "block.h"

/* 0x0217DA70 .. 0x0217DAC8, 23 instructions, 92 bytes.
   Releases +0x4E8, conditionally releases +0x4EC based on the global object
   at 0x10189448, then releases +0x4F0 and +0x4F4. */

typedef struct {
    u8 pad0[0x4E8];
    s32 field_4E8;
    s32 field_4EC;
    s32 field_4F0;
    s32 field_4F4;
} Obj;

extern void func_026C8E48(s32 handle);

void func_0217DA70(Obj *self) {
    func_026C8E48(self->field_4E8);
    if (*(s32 *)((u8 *)*(void **)0x10189448 + 0x30) == 0) {
        func_026C8E48(self->field_4EC);
    }
    func_026C8E48(self->field_4F0);
    func_026C8E48(self->field_4F4);
}
