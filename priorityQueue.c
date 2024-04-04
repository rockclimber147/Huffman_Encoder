#include "hnode.h"

typedef struct QueueNode QueueNode;
struct QueueNode {
    Node *root;
    int priority;
    struct QueueNode *next;
    struct QueueNode *prev;
};

void enqueue(QueueNode **head, QueueNode *val) {
    // THis is responsible for inserting nodes IN ORDER
    // First order by priority
    // If priorities are equal, order by ASCII value of root node
    // If ASCII values are equal, put incoming after
}

QueueNode *dequeue(QueueNode **head) {
    // Returns the head and reassigns head pointer to new head
}

void freeQueue(QueueNode *head) {
    // need to call freeTree on root
}


