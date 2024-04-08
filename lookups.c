#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hnode.h"

#define MAX_PRINTABLE_CHARACTERS 128

int* getCharacterFrequencies(const char *text);
void printCharacterFrequencies(int *characterFrequencies);
void getCodeWordsRecursive(char *codewords[MAX_PRINTABLE_CHARACTERS], Node *root, char *currentString, int charsNeeded);
void getCodeWords(char **codewords, Node *root);
void printCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS]);
char **initializeCodeTable();
void freeCodetable(char **codeTable);
void *getCharacterFrequenciesFromFile(char *filename, int *charFrequencyTable);
int LOOKUP_TESTS();

/**
 * Populates a table with ASCII index values and the amount of times that character was found
 * @param filename The name of the file to read from
 * @return The completed character frequency table
 */
void *getCharacterFrequenciesFromFile(char *filename, int *charFrequencyTable) {
    FILE *input;

    input = fopen("LookupTest.txt", "r");

    if (input == NULL){
        printf("Couldn't open file");
        return NULL;
    }

    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        charFrequencyTable[i] = 0;
    }
    char currentChar;
    do {
        currentChar = fgetc(input);
        charFrequencyTable[currentChar]++;
    } while (currentChar != EOF);

    fclose(input);
}

/**
 * Populates a table with ASCII index values and the amount of times that character was found
 * @param text The string to determine the frequencies of characters
 * @return The completed character frequency table
 */
int* getCharacterFrequencies(const char *text) {
    int *characterFrequencies = malloc(sizeof(int) * MAX_PRINTABLE_CHARACTERS);
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        characterFrequencies[i] = 0;
    }
    while (*text != '\0') {
        characterFrequencies[*text]++;
        text++;
    }
    return characterFrequencies;
}

/**
 * Prints the characters and frequencies of characters that appear once or more
 * @param characterFrequencies an array of character frequencies
 */
void printCharacterFrequencies(int *characterFrequencies) {
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (characterFrequencies[i] != 0) {
            printf("%c : %d\n", i, characterFrequencies[i]);
        }
    }
}

/**
 * Allocates and returns an array of string pointers
 * @return an array of string pointers
 */
char **initializeCodeTable() {
    char **codewords = malloc(sizeof(char*) * MAX_PRINTABLE_CHARACTERS);
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        codewords[i] = NULL;
    }
    return codewords;
}
/**
 * Frees the contents of the codeTable and then the table itself
 * @param codeTable an array of string pointers, some NULL and some not
 */
void freeCodetable(char **codeTable) {
    // free all the pointers that were allocated to something
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (codeTable[i] != NULL) {
            free(codeTable[i]);
        }
    }
    // free the table after all pointers are freed
    free(codeTable);
}

/**
 * Recursively traverses a Huffman tree and associates codewords with ASCII indexes in the codewords array
 * @param codewords An array of strings
 * @param root The root of the Huffman tree
 * @param currentString the current codeword
 * @param charsNeeded The maximum size of a codeword string
 */
void getCodeWordsRecursive(char *codewords[MAX_PRINTABLE_CHARACTERS], Node *root, char *currentString, int charsNeeded) {
    // Base case, leaf has no children so write the code string to the table.
    if (isLeaf(root)) {
        // allocate memory for the code string
        codewords[root->character] = malloc(charsNeeded * sizeof(char));
        // copy the generated code string to the allocated memory
        strcpy(codewords[root->character], currentString);
        return;
    }

    // Not the base case, need to append a '0' to the code word for the left branch and call again
    if (root->left != NULL) {
        // make a temporary string
        char temp[charsNeeded];
        // copy the parent codeword into it
        strcpy(temp, currentString);
        // Append 0 to the end of temporary string
        strcat(temp, "0");
        getCodeWordsRecursive(codewords, root->left, temp, charsNeeded);
    }

    // As above, but right is '1'
    if (root->right != NULL) {
        char temp[charsNeeded];
        strcpy(temp, currentString);
        strcat(temp, "1");
        getCodeWordsRecursive(codewords, root->right, temp, charsNeeded);
    }
}

/**
 * Starts the codeword table population process
 * @param codewords An empty codewords table
 * @param root The root of the Huffman Tree
 */
void getCodeWords(char **codewords, Node *root) {
    // codewords get longer the deeper in the tree so the max characters needed is the depth + 1 for the null character
    int maxCharsNeeded = height(root) + 1;

    if (root->left != NULL) {
        // left code words start with 0
        getCodeWordsRecursive(codewords, root->left, "0", maxCharsNeeded);
    }
    if (root->right != NULL) {
        // right code words start with 1
        getCodeWordsRecursive(codewords, root->right, "1", maxCharsNeeded);
    }
}

/**
 * Prints all codewords in a table with their respective characters
 * @param codewords
 */
void printCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS]) {
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (codewords[i] != NULL) {
            printf("%c: %s\n", i, codewords[i]);
        }
    }
}
