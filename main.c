#include <stdio.h>
#include <string.h>
#include "lookups.h"
#include "hnode.h"
#include "priorityQueue.h"
#include "createTree.h"
#include "UnitTests.h"

#define OUTPUT_PREFIX "OUT_"
#define DECODED_PREFIX "DEC_"

TreeNode * getHuffmanTreeFromFrequencyTable (int *charFrequencyTable) {
    QueueNode *head = generatePriorityQueue(charFrequencyTable);
//    printf("The priority Queue generated is:\n");
//    printQueue(head);

    TreeNode *huffmanTree = createHuffmanTree(&head);

    freeQueue(head);

    return huffmanTree;
}

char **getCodeTableFromTree(TreeNode *root) {
    char **codeTable = initializeCodeTable();
    getCodeWords(codeTable, root);
    printf("The codewords are:\n");
    printCodeWords(codeTable);
    return codeTable;
}

void writeCompressedString(char **codeTable, char *filename, char *outputFileName) {
    FILE *input;
    FILE *output;

    input = fopen(filename, "r");

    if (!input){
        printf("Couldn't open file");
        return;
    }

    output = fopen(outputFileName ,"w");
    if (!output){
        printf("Couldn't create output file");
        return;
    }

    char currentChar;
    do {
        currentChar = (char) fgetc(input);
        if (currentChar != EOF) {
            fprintf(output, "%s", codeTable[currentChar]);
        }
    } while (currentChar != EOF);
    fclose(output);
}

int getTextFileSizeInBits(char *fileName) {
    FILE *input;
    int totalChars = 0;

    input = fopen(fileName, "r");

    if (input == NULL){
        printf("Couldn't open file");
        return -1;
    }
    char currentChar;
    do {
        currentChar = (char) fgetc(input);
        totalChars++;
    } while (currentChar != EOF);
    fclose(input);
    return totalChars;
}

void decodeToFile(char *codedFileName, char *outputFileName, TreeNode *root) {
    FILE *codedFile;
    FILE *decodedFile;

    codedFile = fopen(codedFileName, "r");

    if (codedFile == NULL){
        printf("Couldn't open coded file");
        return;
    }
    decodedFile = fopen(outputFileName, "w");

    if (decodedFile == NULL){
        printf("Couldn't open output file");
        return;
    }
    TreeNode *current = root;
    char currentChar = (char) fgetc(codedFile);
    while (currentChar != EOF) {
        if (currentChar == '0') {
            current = current-> left;
        } else if (currentChar == '1') {
            current = current-> right;
        } else {
            printf("UNEXPECTED CHARACTER WHEN DECODING: %c\n", currentChar);
        }

        if (isLeaf(current)) {
            fprintf(decodedFile, "%c", current->character);
            current = root;
        }

        currentChar = (char) fgetc(codedFile);
    }
    fclose(codedFile);
    fclose(decodedFile);
}

int main() {
    // specify file name
    char *filename = "Example.txt";
    char outputFileName[100] = OUTPUT_PREFIX;
    strcat(outputFileName, filename);
    char decodedFileName[100] = DECODED_PREFIX;
    strcat(decodedFileName, filename);

    int fileSizeInBits = getTextFileSizeInBits(filename) * 8;
    int outputFileSizeInBits;
    printf("\n%s takes uses %d bits at 8 bits per character\n\n", filename, fileSizeInBits);

    // get char frequency table from file
    int charFrequencyTable[MAX_PRINTABLE_CHARACTERS];
    getCharacterFrequenciesFromFile(filename, charFrequencyTable);

    // display frequencies
    printf("The character counts for %s are:\n", filename);
    printCharacterFrequencies(charFrequencyTable);
    printf("\n");

    // get tree from frequency table
    TreeNode *root = getHuffmanTreeFromFrequencyTable(charFrequencyTable);

    // get code table from tree
    char **codeTable = getCodeTableFromTree(root);
    printf("\n");

    // get size of compressed string
    writeCompressedString(codeTable, filename, outputFileName);

    outputFileSizeInBits = getTextFileSizeInBits(outputFileName) - 1;
    printf("\nBits needed to encode: %d\n", outputFileSizeInBits);
    printf("output file is %.2f%% smaller than input file\n",
           100 * (1 - ((float) outputFileSizeInBits) / ((float) fileSizeInBits)));

    printf("\nDecoding to %s\n", decodedFileName);
    decodeToFile(outputFileName, decodedFileName, root);
    printf("\n");
    getTextFileSizeInBits(decodedFileName);

    freeTree(root);
    freeCodetable(codeTable);
    printf("\n");
    return 0;
}
