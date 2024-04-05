#include "hnode.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode QueueNode;
struct QueueNode {
    Node *root;
    int priority;
    struct QueueNode *next;
};

void insertNodeBefore(QueueNode *current, QueueNode *val) {
    QueueNode *temp = current -> next;
    current -> next = val;
    val -> next = temp;
}

QueueNode enqueue(QueueNode **head, QueueNode *val) {
    // THis is responsible for inserting nodes IN ORDER
    if (*head == NULL) {
        *head = val;
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
            //compare ascii, insert after current
            if (val -> root -> character <= current -> next -> root -> character) {
                insertNodeBefore(current, val);
                return **head;
            }
        } else if (val -> priority < current -> next -> priority) {
            insertNodeBefore(current, val);
            return **head;
        }
        current = current -> next;
    }
    current -> next = val;
    return **head;
}

QueueNode *dequeue(QueueNode **head) {
    // Returns the head and reassigns head pointer to new head
}

void freeQueue(QueueNode *head) {
    // need to call freeTree on root
}


