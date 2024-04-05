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

void printCharacterFrequencies(int *characterFrequencies) {
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (characterFrequencies[i] != 0) {
            printf("%c : %d\n", i, characterFrequencies[i]);
        }
    }
}

void getCodeWordsRecursive(char *codewords[MAX_PRINTABLE_CHARACTERS], Node *root, char *currentString, int charsNeeded) {
    if (isLeaf(root)) {
        strcpy(codewords[root->character], currentString);
        return;
    }

    if (root->left != NULL) {
        char temp[charsNeeded];
        strcpy(currentString, temp);        // make temporary string copy of incoming string
        strcat(temp, "0");                   // Append 0 to the end of temporary string
        getCodeWordsRecursive(codewords, root->left, temp, charsNeeded);
    }

    if (root->right != NULL) {
        char temp[charsNeeded];
        strcpy(currentString, temp);
        strcat(temp, "1");
        getCodeWordsRecursive(codewords, root->right, temp, charsNeeded);
    }
}

void getCodeWords(char **codewords, Node *root) {
    int maxCharsNeeded = height(root) + 1; // codewords get longer the deeper in the tree so the max characters needed
    // is the depth +1 for the \0
    if (root->left != NULL) {
        getCodeWordsRecursive(codewords, root->left, "0", maxCharsNeeded);
    }
    if (root->right == NULL) {
        getCodeWordsRecursive(codewords, root->left, "1", maxCharsNeeded);
    }
}

void printCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS]) {
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        printf("%c: %s\n", i, codewords[i]);
    }
}

