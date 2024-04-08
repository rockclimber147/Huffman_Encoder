#include <stdio.h>
#include <stdlib.h>
#include "lookups.h"
#include "hnode.h"
#include "priorityQueue.h"
#include "createTree.h"
#include "UnitTests.h"
#include "createTree.h"



Node * getHuffmanTreeFromFile (char *filename) {
    int charFrequencyTable[MAX_PRINTABLE_CHARACTERS];
    getCharacterFrequenciesFromFile(filename, charFrequencyTable);


    printf("The character counts for %s are:\n", filename);
    printCharacterFrequencies(charFrequencyTable);
    printf("\n");

    QueueNode *head = generatePriorityQueue(charFrequencyTable);
    printf("The priority Queue generated is:\n");
    printQueue(head);

    //TODO debug print
    printf("\nwhich has size %d\n", nodeCount(head));
    //// end debug print

    Node *huffmanTree = createHuffmanTree(&head);

    freeQueue(head);

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
//    TEST_printTree();
    Node *root = getHuffmanTreeFromFile("LookupTest.txt");
    char **codeTable = getCodeTableFromTree(root);

    return 0;
}
