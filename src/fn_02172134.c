#include "block.h"

/* 0x02172134 .. 0x02172170, 16 instructions, 64 bytes.
   Calls a no-argument setup routine, then passes this object and a local -1
   to the second helper. */

extern void func_021720C0(void);
extern void func_02171EE8(s32 arg0, s32 *out);

void func_02172134(s32 arg0) {
    s32 value;

    func_021720C0();
    value = -1;
    func_02171EE8(arg0, &value);
}
