#include "block.h"

typedef struct StartupNode {
    struct StartupNode *next;
} StartupNode;

extern StartupNode *startup_link;

void func_02BCF688(StartupNode *node) {
    StartupNode *head;

    if (node->next != 0) return;
    head = startup_link;
    if (node == head) return;
    startup_link = node;
    node->next = head;
}
