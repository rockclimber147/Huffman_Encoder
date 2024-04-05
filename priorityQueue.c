#include <stdio.h>
#include <stdlib.h>
#include "hnode.h"

typedef struct QueueNode QueueNode;
struct QueueNode {
    Node *root;
    int priority;
    struct QueueNode *next;
    struct QueueNode *prev;
};

void enqueue(QueueNode **head, QueueNode *val) {

}

QueueNode *dequeue(QueueNode **head) {
    if (*head == NULL) {
        return NULL;
    }
    QueueNode *temp = *head;
    *head = (*head)->next;

    return temp;
}

void freeQueue(QueueNode *head) {
    while (head != NULL) {
        QueueNode *temp = head;
        head = head->next;
        freeTree(temp->root);
        free(temp);
    }
}
