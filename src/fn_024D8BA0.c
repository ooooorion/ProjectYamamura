#include "block.h"

/* 0x024D8BA0 .. 0x024D8BB0, 5 instructions, 20 bytes.
   True when +0x3DC is four. */

typedef struct { u8 pad0[0x3DC]; s32 field_3DC; } Obj;
s32 func_024D8BA0(Obj *self) { return (self->field_3DC ^ 4) == 0; }
