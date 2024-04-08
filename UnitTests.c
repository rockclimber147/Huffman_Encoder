//
// Created by Drumm on 2024-04-06.
//

#include <stdio.h>
#include <stdlib.h>
#include "lookups.h"
#include "priorityQueue.h"
#include "hnode.h"
#include "createTree.h"

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
    printf("\n");
    freeQueue(manual);

    return 0;
}

/**
 * Generates a Huffman tree, generates and prints the codeword table, and frees all allocated memory
 */
int LOOKUP_TESTS() {

    int* frequencies = getCharacterFrequenciesFromFile("LookupTest.txt");
    if (frequencies == NULL) {
        return 1;
    }

    printCharacterFrequencies(frequencies);
    free(frequencies);

    Node *A = createNode();
    A->character = 'A';
    Node *B = createNode();
    B->character = 'B';
    Node *C = createNode();
    C->character = 'C';
    Node  *D = createNode();
    D->character = 'D';
    Node *E = createNode();
    E->character = 'E';

    Node *AB = createNode();
    AB->left = A;
    AB->right = B;
    Node *ABC = createNode();
    ABC->left = AB;
    ABC->right = C;
    Node *DE = createNode();
    DE->left = D;
    DE->right = E;
    Node *ABCDE = createNode();
    ABCDE->left = ABC;
    ABCDE ->right = DE;
    Node *root = ABCDE;

    char **codewords = malloc(sizeof(char*) * MAX_PRINTABLE_CHARACTERS);
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        codewords[i] = NULL;
    }
    getCodeWords(codewords, root);
    printCodeWords(codewords);

    freeTree(root);
    freeCodetable(codewords);
    return 0;
}

int PRIORITY_QUEUE_TEST_ALICE() {
    Node *A = createNode();
    A->character = 'A';
    Node *B = createNode();
    B->character = 'B';
    Node *C = createNode();
    C->character = 'C';

    QueueNode *Aqn = createQueueNode(A, 3);
    QueueNode *Bqn = createQueueNode(B, 2);
    QueueNode *Cqn = createQueueNode(C, 1);

    QueueNode *head = enqueue(Bqn, Aqn);
    head = enqueue(head, Cqn);

    while (head->next != NULL) {
        printf("%c ->", head->root->character);
        head = head->next;
    }
    printf("%c ->", head->root->character);

    return 0;
}

int CREATE_TREE_ALEX_TEST() {
    int* frequencies = getCharacterFrequenciesFromFile("LookupTest.txt");
    if (frequencies == NULL) {
        return 1;
    }

    printCharacterFrequencies(frequencies);

    QueueNode *priorityQueue = generatePriorityQueue(frequencies);
    printQueue(priorityQueue);
    free(frequencies);
    return 0;
}

////////////////////////////////// THE FOLLOWING IS FOR TESTING ALEX'S CODE:

//Node* createHuffmanTree(QueueNode** head) {
//    while (*head != NULL && (*head)->next->next != NULL) {
//        // Dequeue two nodes with the lowest frequencies
//        QueueNode* node1 = dequeue(head);
//        QueueNode* node2 = dequeue(head);
//
//        // Create a new internal node with node1 and node2 as children
//        Node* newNode = createNode();
//        newNode->left = node1->root;
//        newNode->right = node2->root;
//
//        // Enqueue the new node back into the priority queue
//        QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
//        newQueueNode->root = newNode;
//        newQueueNode->priority = node1->priority + node2->priority;
//        newQueueNode->next = NULL;
//        enqueue(*head, newQueueNode);
//
//        // Free memory for the dequeued nodes
//        freeQueue(node1);
//        freeQueue(node2);
//    }
//
//    // The last queueNode in priority queue is the root node of Huffman Tree
//    if (*head != NULL) {
//        Node* huffmanRoot = (*head)->root;
//        return huffmanRoot;
//    }
//
//    return NULL; // If the queue is empty
//}

/**
 * Generates a priority queue from all nonzero characters and their frequencies in the input table
 * @return a pointer to a priority queue
 */
//QueueNode *generatePriorityQueue(int *frequencyTable) {
//    QueueNode *newPriorityQueue = NULL;
//
//    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
//        if (frequencyTable[i] != 0) {
//            // Creating a new tree node for the character
//            Node *newRoot = createNode();
//            newRoot->character = (char) i;
//
//            // Creating a new queue node
//            QueueNode *newQueueNode = createQueueNode(newRoot, frequencyTable[i]);
//
//            // Enqueue the new node into the priority queue
//            if (newPriorityQueue == NULL) {
//                newPriorityQueue = newQueueNode; // set newQueueNode as head if empty priority queue
//            } else {
//                newPriorityQueue = enqueue(newPriorityQueue, newQueueNode); // Enqueue in order of priority (frequency)
//            }
//        }
//    }
//    return newPriorityQueue;
//}

void TEST_freeTree() {
    Node *A = createNode();
    A->character = 'A';
    Node *B = createNode();
    A->character = 'B';
    Node *C = createNode();
    A->character = 'C';
    A->right = B;
    B->right = C;
    freeTree(A);
}

void TEST_printTree(){
    Node *A = createNode();
    A->character = 'A';
    Node *B = createNode();
    B->character = 'B';
    Node *C = createNode();
    C->character = 'C';
    A->right = B;
    B->right = C;
    printTree(A);
    printf("\n");
    printTree(B);
    printf("\n");
    printTree(C);
    freeTree(A);
}