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
QueueNode *createQueueNode();
void enqueue(QueueNode **head, QueueNode *val);
QueueNode* dequeue(QueueNode **head);
void freeQueue(QueueNode *head);
#endif //HUFFMAN_ENCODER_PRIORITYQUEUE_H
