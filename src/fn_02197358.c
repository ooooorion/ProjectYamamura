#include "block.h"

/* 0x02197358 .. 0x02197398, 17 instructions, 68 bytes.
   Runs one no-argument setup routine, then forwards this object through three
   teardown helpers. */

extern void func_0211BD48(void);
extern void func_0212F7E0(s32 arg0);
extern void func_0212D584(s32 arg0);
extern void func_0211BD70(s32 arg0);

void func_02197358(s32 arg0) {
    func_0211BD48();
    func_0212F7E0(arg0);
    func_0212D584(arg0);
    func_0211BD70(arg0);
}
