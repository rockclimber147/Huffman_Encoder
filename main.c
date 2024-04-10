#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lookups.h"
#include "hnode.h"
#include "priorityQueue.h"
#include "createTree.h"
#include "UnitTests.h"
#include "createTree.h"

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
    printf("\n\nThe codewords are:\n");
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
    char byte[8];
    int count = 0;

    //TODO: write the string of binary digits to file
    for (int i = 0; i < strlen(string); i++) {
        if (count < 8) {
            byte[count] = string[i];
            count++;
        } else {
            char c = strtol(byte, (char **) NULL, 2);
            fputc(c, file);
            count = 0;
            byte[count] = string[i];
            count++;
        }
    }

    while (count < 8) {
        byte[count] = '0';
        count++;
    }

    char c = strtol(byte, (char **) NULL, 2);
    fputc(c, file);
    fclose(file);
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

int displayFileContentsWitsSizeInBits(char *fileName) {
    FILE *input;
    int totalChars = 0;

    input = fopen(fileName, "r");

    if (input == NULL){
        printf("Couldn't open file");
        return -1;
    }
    printf("Printing contents of %s:\n", fileName);
    char currentChar;
    do {
        currentChar = (char) fgetc(input);
        printf("%c", currentChar);
        totalChars++;
    } while (currentChar != EOF);
    printf("\n");
    fclose(input);
    return totalChars;
}

int main() {
    // specify file name
    char *filename = "LookupTest.txt";
    char outputFileName[100] = OUTPUT_PREFIX;
    strcat(outputFileName, filename);
    char decodedFileName[100] = DECODED_PREFIX;
    strcat(decodedFileName, filename);

    int fileSizeInBits = displayFileContentsWitsSizeInBits(filename) * 8;
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

    outputFileSizeInBits = displayFileContentsWitsSizeInBits(outputFileName) - 1;
    printf("\nBits needed to encode: %d\n", outputFileSizeInBits);
    printf("output file is %.2f%% smaller than input file",
           100 * (1 - ((float) outputFileSizeInBits) / ((float) fileSizeInBits)));



    freeTree(root);
    printf("\n");
    return 0;
}
