#include <stdio.h>
#include <stdlib.h>
#include "lookups.h"
#include "hnode.h"
#include "priorityQueue.h"
#include "createTree.h"
#include "UnitTests.h"
#include "createTree.h"



Node * getHuffmanTreeFromFile (char *filename) {
    int *charFrequencies = getCharacterFrequenciesFromFile(filename);
    if (!charFrequencies) {
        printf("Couldn't get char frequencies\n");
        return NULL;
    }

    printf("The character counts for %s are:\n", filename);
    printCharacterFrequencies(charFrequencies);
    printf("\n");

    QueueNode *head = generatePriorityQueue(charFrequencies);
    printf("The priority Queue generated is:\n");
    printQueue(head);
    Node *huffmanTree = createHuffmanTree(&head);

    freeQueue(head);
    free(charFrequencies);

    return huffmanTree;
}

char **getCodeTableFromTree(Node *root) {
    char **codeTable = initializeCodeTable();
    getCodeWords(codeTable, root);
    printf("The codewords are:\n");
    printCodeWords(codeTable);
    return codeTable;
}

int main() {
//    PRIORITY_QUEUE_PRINT_TEST();
//    LOOKUP_TESTS();
//    PRIORITY_QUEUE_TEST_ALICE();
//    CREATE_TREE_ALEX_TEST();
//    TEST_freeTree();
    Node *root = getHuffmanTreeFromFile("LookupTest.txt");
    char **codeTable = getCodeTableFromTree(root);

    return 0;
}
