#include <stdio.h>
#include <stdlib.h>
#include "hnode.h"
#include "lookups.h"

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
QueueNode *createDefaultQueueNode() {
    QueueNode *queueNode = (QueueNode *) malloc(sizeof (QueueNode));
    queueNode->root = NULL;
    queueNode->priority= 0;
    queueNode->next=NULL;

    return queueNode;
}

QueueNode *createQueueNode(Node *node, int priority) {
    QueueNode *queueNode = (QueueNode *) malloc(sizeof (QueueNode));
    queueNode->root = node;
    queueNode->priority=priority;
    queueNode->next=NULL;

    return queueNode;
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

QueueNode* enqueue(QueueNode *head, QueueNode *val) {
    // This is responsible for inserting nodes IN ORDER
    if (head == NULL) {
        head = val;
        return head;
    } else {
        if ((val -> priority < head->priority) ||
        (val -> priority == head-> priority && val -> root -> character < head -> root -> character)) {
            // insert before head if val.priority < head.priority OR val.priority == head.priority AND val.char.ascii < head.char.ascii
            val -> next = head;
            return val;
        }
    }

    QueueNode *current = head;
    while (current -> next != NULL) {
        // if priorities are equal
        if (val -> priority == current -> next -> priority) {
            //compare ascii, insert after current if val's ascii is less than next node's ascii
            if (val -> root -> character < current -> next -> root -> character) {
                insertNodeBefore(current, val);
                return head;
            }
        } else if (val -> priority < current -> next -> priority) {
            // if val.priority is less than next node's priority, insert val before next node
            insertNodeBefore(current, val);
            return head;
        }
        // traverse to next node
        current = current -> next;
    }
    // if current -> next == NULL, insert val to the end of the queue
    current -> next = val;
    return head;
}

//QueueNode dequeue(QueueNode **head) {
//    QueueNode *temp = *head;
//    *head = (*head)->next;
//
//    return *temp;
//}
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

/**
 * Prints the queueNode data in the format (rootCharacter priority modified priority)->
 * @param node The node to print
 */
void printQueueNode(QueueNode *node) {
    while(node->next != NULL){
        printf("(c:%c p:%d Mp:%d)->", node->root->character, node->priority, getPriority(node));
        node = node->next;
    }
    // print the last remaining node
    printf("(c:%c p:%d Mp:%d)->", node->root->character, node->priority, getPriority(node));

}

/**
 * Recursively prints a priorityQueue
 * @param head The head of a priority queue
 */
void printQueue(QueueNode *head) {
    if (head) {
        printQueueNode(head);
        printQueue(head->next);
    }
    printf("\n");
}

////////////////////////////////// THE FOLLOWING IS FOR TESTING ALEX'S CODE:

Node* createHuffmanTree(QueueNode** head) {
    while (*head != NULL && (*head)->next->next != NULL) {
        // Dequeue two nodes with the lowest frequencies
        QueueNode* node1 = dequeue(head);
        QueueNode* node2 = dequeue(head);

        // Create a new internal node with node1 and node2 as children
        Node* newNode = createNode();
        newNode->left = node1->root;
        newNode->right = node2->root;

        // Enqueue the new node back into the priority queue
        QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
        newQueueNode->root = newNode;
        newQueueNode->priority = node1->priority + node2->priority;
        newQueueNode->next = NULL;
        enqueue(head, newQueueNode);

        // Free memory for the dequeued nodes
        freeQueue(node1);
        freeQueue(node2);
    }

    // The last queueNode in priority queue is the root node of Huffman Tree
    if (*head != NULL) {
        Node* huffmanRoot = (*head)->root;
        return huffmanRoot;
    }

    return NULL; // If the queue is empty
}

/**
 * Generates a priority queue from all nonzero characters and their frequencies in the input table
 * @return a pointer to a priority queue
 */
QueueNode *generatePriorityQueue(int *frequencyTable) {
    QueueNode *newPriorityQueue = NULL;

    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (frequencyTable[i] != 0) {
            // Creating a new tree node for the character
            Node *newRoot = createNode();
            newRoot->character = i;

            // Creating a new queue node
            QueueNode *newQueueNode = createQueueNode(newRoot, frequencyTable[i]);

            // Enqueue the new node into the priority queue
            if (newPriorityQueue == NULL) {
                newPriorityQueue = newQueueNode; // set newQueueNode as head if empty priority queue
            } else {
                newPriorityQueue = enqueue(newPriorityQueue, newQueueNode); // Enqueue in order of priority (frequency)
            }
        }
    }
    return newPriorityQueue;
}

//int main() {
//    int* frequencies = getCharacterFrequenciesFromFile("LookupTest.txt");
//    if (frequencies == NULL) {
//        return 1;
//    }
//
//    printCharacterFrequencies(frequencies);
//
//    QueueNode *priorityQueue = generatePriorityQueue(frequencies);
//    printQueueNode(priorityQueue);
//    free(frequencies);
//    return 0;
//}
