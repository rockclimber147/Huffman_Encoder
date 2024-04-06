//
// Created by Drumm on 2024-04-06.
//

#include <stdio.h>
#include <stdlib.h>
#include "lookups.h"
#include "priorityQueue.h"
#include "hnode.h"

int PRIORITY_QUEUE_PRINT_TEST() {
    QueueNode *p1 = createDefaultQueueNode();
    Node *p1root = createNode();
    p1->root = p1root;
    p1root->character = 'A';
    p1->priority = 1;

    QueueNode *p2 = createDefaultQueueNode();
    Node *p2root = createNode();
    p2->root = p2root;
    p2root->character = 'B';
    p2->priority = 2;

    QueueNode *p3 = createDefaultQueueNode();
    Node *p3root = createNode();
    p3->root = p3root;
    p3root->character = 'C';
    p3->priority = 2;

    // make queue manually
    p1->next = p2;
    p2->next = p3;

    QueueNode *manual = p1;

    printQueue(p1);
    freeQueue(manual);

    return 0;
}