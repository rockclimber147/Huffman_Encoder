#include <stdlib.h>
#include <stdio.h>
#include "hnode.h"

#define MAX_PRINTABLE_CHARACTERS 128

int* getCharacterFrequencies(const char *text);
void printCharacterFrequencies(int *characterFrequencies);

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

void getCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS], Node *root) {

}
