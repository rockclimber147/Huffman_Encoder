#include <stdio.h>
#include <stdlib.h>
#include "hnode.h"

typedef struct QueueNode QueueNode;
struct QueueNode {
    Node *root;
    int priority;
    struct QueueNode *next;
};

/**
 * Allocates and initializes a default QueueNode
 * @return pointer to new QueueNode
 */
QueueNode *createQueueNode() {
    QueueNode *node = (QueueNode *) malloc(sizeof (QueueNode));
    node->root = NULL;
    node->priority=0;
    node->next=NULL;

    return node;
}


/**
 * Returns the absolute priority of a QueueNode
 * @param node The QueueNode to get the priority of
 * @return The priority of the QueueNode
 */
int getPriority(QueueNode *node) {
    return node->priority * 1000 + node->root->character;
}

void insertNodeBefore(QueueNode *current, QueueNode *val) {
    QueueNode *temp = current -> next;
    current -> next = val;
    val -> next = temp;
}

QueueNode enqueue(QueueNode **head, QueueNode *val) {
    // THis is responsible for inserting nodes IN ORDER
    if (*head == NULL) {
        *head = val;
        return **head;
    } else {
        if ((val -> priority < (*head) -> priority) ||
        (val -> priority == (*head) -> priority && val -> root -> character <= (*head) -> root -> character)) {
            // insert before head if val.priority < head.priority OR val.priority == head.priority AND val.char.ascii <= head.char.ascii
            val -> next = (*head);
            return *val;
        }
    }

    QueueNode *current = *head;
    while (current -> next != NULL) {
        // if priorities are equal
        if (val -> priority == current -> next -> priority) {
            //compare ascii, insert after current if val's ascii is less than next node's ascii
            if (val -> root -> character < current -> next -> root -> character) {
                insertNodeBefore(current, val);
                return **head;
            }
        } else if (val -> priority < current -> next -> priority) {
            // if val.priority is less than next node's priority, insert val before next node
            insertNodeBefore(current, val);
            return **head;
        }
        // traverse to next node
        current = current -> next;
    }
    // if current -> next == NULL, insert val to the end of the queue
    current -> next = val;
    return **head;
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

/**
 * Counts the total amount of QueueNodes in a priority queue
 * @param head The head of the queue
 * @return the number of nodes
 */
int nodeCount(QueueNode *head) {
    int count = 0;
    if (!head) {
        return count;
    }
    QueueNode *current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

void printQueueNode(QueueNode *node) {
    printf("(rootc: %c p: %d Mp: %d)->", node->root->character, node->priority, getPriority(node));
}

int PRIORITY_QUEUE_TEST() {
    return 0;
}
