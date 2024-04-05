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
void LOOKUP_TESTS();

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

char **initializeCodeTable() {
    char **codewords = malloc(sizeof(char*) * MAX_PRINTABLE_CHARACTERS);
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        codewords[i] = NULL;
    }
    return codewords;
}

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

void printCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS]) {
    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (codewords[i] != NULL) {
            printf("%c: %s\n", i, codewords[i]);
        }
    }
}


void LOOKUP_TESTS() {
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
}