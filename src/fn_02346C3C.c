#include "block.h"

/* 0x02346C3C .. 0x02346C94, 23 instructions, 92 bytes.
   Lazily initializes the +0xA8 object. */

extern void func_020DCD94(void *value);
extern void func_02616AA8(s32 value, s32 flag);
void func_02346C3C(void *self) {
    if (*(u8 *)((u8 *)self + 0xA6) == 0) {
        func_020DCD94((u8 *)self + 0xA8);
        if (*(s32 *)((u8 *)self + 0xA8) == 0) {
            func_02616AA8(*(s32 *)((u8 *)self + 0x8C), 1);
            *(u8 *)((u8 *)self + 0xA6) = 1;
        }
    }
}
