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
    Node *D = createNode();
    D->character = 'D';
    Node *E = createNode();
    E->character = 'E';

    Node *AA = createNode();
    AA->character = 'A';

    QueueNode *Aqn = createQueueNode(A, 1);
    QueueNode *AAqn = createQueueNode(AA, 1);
    QueueNode *Bqn = createQueueNode(B, 2);
    QueueNode *Cqn = createQueueNode(C, 1);
    QueueNode *Dqn = createQueueNode(D, 4);
    QueueNode *Eqn = createQueueNode(E, 5);

    QueueNode *head = createDefaultQueueNode();
    *head = enqueue(&Bqn, Aqn);
    *head = enqueue(&head, Dqn);
    *head = enqueue(&head, Cqn);
//    *head = enqueue(&head, AAqn);
//    *head = dequeue(&head);

//    while (head != NULL) {
//        printQueueNode(head);
//        *head = dequeue(&head);
//    }

    while (head->next != NULL) {
        printQueueNode(head);
        printf("%c", head->root->character);
//        head = head->next;
        *head = dequeue(&head);

    }
    printf("\n-------\n");
    QueueNode *test = createDefaultQueueNode();
    *test = dequeue(&head);
    printQueueNode(test);
    printf("%c", test->root->character);
    printf("\n-------\n");
    printQueueNode(head);
    printf("%c", head->root->character);

    return 0;
}