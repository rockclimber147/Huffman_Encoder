#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//reads from file and converts content to a string containing all encoded binary digits
char* encode(char* filename, char** codeTable) {
    FILE *input = fopen(filename, "r");
    char character;

    if (input == NULL){
        printf("Couldn't open file");
        return NULL;
    }

    char* encodedString = (char *)malloc(MAX_PRINTABLE_CHARACTERS*sizeof (char));

    while ((character = fgetc(input)) != EOF) {
        encodedString = (char *)realloc(encodedString, strlen(codeTable[(int) character]) * sizeof(char));
        if (encodedString == NULL) {
            printf("Memory reallocation failed.\n");
            fclose(input);
            return NULL;
        }
        strcat(encodedString, codeTable[(int) character]);
        printf("%s\n", encodedString);
    }
    fclose(input);
    return encodedString;
}

void compress(char* string) {
    FILE *file = fopen("output.txt", "w");
    if (!file) {
        printf("Error: Unable to create file.\n");
        return;
    }

    //TODO: write the string of binary digits to file

    fclose(file);
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
    char* compressedString = encode("LookupTest.txt", codeTable);
    if (compressedString != NULL) {
        printf("Compressed string: %s\n", compressedString);
        compress(compressedString);
        free(compressedString);
    }

    return 0;
}
