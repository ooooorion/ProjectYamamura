#include "block.h"

/* 0x023612D0 .. 0x023612D8, 3 instructions, 12 bytes.
   Masks the low nibble of the pointed-to word. */

s32 func_023612D0(s32 *value) { return *value & 0xF; }
