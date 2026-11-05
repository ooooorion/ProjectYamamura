#include "block.h"

/* 0x024DF664 .. 0x024DF670, 4 instructions, 16 bytes.
   Returns the nested byte at inner +0x64, then +0x368. */

typedef struct { u8 pad0[0x10]; void *field_10; } Obj;
typedef struct { u8 pad0[0x64]; void *field_64; } Inner;
typedef struct { u8 pad0[0x368]; u8 field_368; } Deep;
u8 func_024DF664(Obj *self) {
    Inner *inner;
    Deep *deep;

    inner = self->field_10;
    deep = inner->field_64;
    return deep->field_368;
}
