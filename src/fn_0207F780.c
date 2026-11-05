#include "block.h"

/* 0x0207F780 .. 0x0207F7A4, 10 instructions, 40 bytes.
   Same shape as 0x0207C970 but accepts kind 4 at +0x04. */

typedef struct {
    s32 tag;
    s32 kind;
} Obj;

s32 func_0207F780(Obj *self) {
    if (self->tag == 0 && self->kind == 4) {
        return 1;
    }
    return 0;
}
