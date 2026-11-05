#include "block.h"

/* 0x0207C970 .. 0x0207C994, 10 instructions, 40 bytes.
   Predicate over two leading words: a zero tag at +0x00 and kind 0x15 at
   +0x04. The 1/0 result is materialised explicitly on both exits. */

typedef struct {
    s32 tag;
    s32 kind;
} Obj;

s32 func_0207C970(Obj *self) {
    if (self->tag == 0 && self->kind == 0x15) {
        return 1;
    }
    return 0;
}
