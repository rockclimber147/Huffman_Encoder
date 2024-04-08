#include <stdio.h>
#include <stdlib.h>
#include "lookups.h"
#include "priorityQueue.h"
#include "hnode.h"
#include "createTree.h"

int PRIORITY_QUEUE_PRINT_TEST() {
    QueueNode *p1 = createDefaultQueueNode();
    TreeNode *p1root = createNode();
    p1->root = p1root;
    p1root->character = 'A';
    p1->priority = 1;

    QueueNode *p2 = createDefaultQueueNode();
    TreeNode *p2root = createNode();
    p2->root = p2root;
    p2root->character = 'B';
    p2->priority = 2;

    QueueNode *p3 = createDefaultQueueNode();
    TreeNode *p3root = createNode();
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

    int frequencies[MAX_PRINTABLE_CHARACTERS];
    getCharacterFrequenciesFromFile("LookupTest.txt", frequencies);

    printCharacterFrequencies(frequencies);

    TreeNode *A = createNode();
    A->character = 'A';
    TreeNode *B = createNode();
    B->character = 'B';
    TreeNode *C = createNode();
    C->character = 'C';
    TreeNode  *D = createNode();
    D->character = 'D';
    TreeNode *E = createNode();
    E->character = 'E';

    TreeNode *AB = createNode();
    AB->left = A;
    AB->right = B;
    TreeNode *ABC = createNode();
    ABC->left = AB;
    ABC->right = C;
    TreeNode *DE = createNode();
    DE->left = D;
    DE->right = E;
    TreeNode *ABCDE = createNode();
    ABCDE->left = ABC;
    ABCDE ->right = DE;
    TreeNode *root = ABCDE;

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
    TreeNode *A = createNode();
    A->character = 'A';
    TreeNode *B = createNode();
    B->character = 'B';
    TreeNode *C = createNode();
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

void TEST_freeTree() {
    TreeNode *A = createNode();
    A->character = 'A';
    TreeNode *B = createNode();
    A->character = 'B';
    TreeNode *C = createNode();
    A->character = 'C';
    A->right = B;
    B->right = C;
    freeTree(A);
}

void TEST_printTree(){
    TreeNode *A = createNode();
    A->character = 'A';
    TreeNode *B = createNode();
    B->character = 'B';
    TreeNode *C = createNode();
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