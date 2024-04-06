//
// Created by dayle on 2024-04-04.
//

#ifndef HUFFMAN_ENCODER_PRIORITYQUEUE_H
#define HUFFMAN_ENCODER_PRIORITYQUEUE_H
#include "hnode.h"
typedef struct QueueNode QueueNode;
struct QueueNode {
    Node *root;
    int priority;
    struct QueueNode *next;
    struct QueueNode *prev;
};
QueueNode *createQueueNode(Node *node, int priority);
QueueNode *createDefaultQueueNode();
QueueNode enqueue(QueueNode **head, QueueNode *val);
QueueNode dequeue(QueueNode **head);
int nodeCount(QueueNode *head);
void freeQueue(QueueNode *head);
void printQueueNode(QueueNode *node);
void printQueue(QueueNode *head);
int PRIORITY_QUEUE_PRINT_TEST();
int PRIORITY_QUEUE_TEST_ALICE();
#endif //HUFFMAN_ENCODER_PRIORITYQUEUE_H
