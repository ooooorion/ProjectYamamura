#include "block.h"

/* 0x02025B78 .. 0x02025B90, 7 instructions, 28 bytes.
   Stores both pointers, marks the owner at +0x14D, and stamps each callee at
   +0x1BC. The statement order is visible in the target: a's stamp is written
   before the second pointer is stored. */

typedef struct {
    u8 pad0[444];
    u8 flag_444;
} Node;

typedef struct {
    u8 pad0[128];
    Node *node_128;
    Node *node_132;
    u8 pad_136[197];
    u8 flag_333;
} Obj;

void func_02025B78(Obj *self, Node *a, Node *b) {
    self->node_128 = a;
    self->flag_333 = 1;
    a->flag_444 = 1;
    self->node_132 = b;
    b->flag_444 = 1;
}
