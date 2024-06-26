//
// Created by dayle on 2024-04-02.
//

#ifndef HUFFMAN_ENCODER_LOOKUPS_H
#define HUFFMAN_ENCODER_LOOKUPS_H

#include "hnode.h"

#define MAX_PRINTABLE_CHARACTERS 128

int* getCharacterFrequencies(const char *text);
void printCharacterFrequencies(int *characterFrequencies);
void getCodeWordsRecursive(char *codewords[MAX_PRINTABLE_CHARACTERS], TreeNode *root, char *currentString, int charsNeeded);
void getCodeWords(char **codewords, TreeNode *root);
void printCodeWords(char *codewords[MAX_PRINTABLE_CHARACTERS]);
char **initializeCodeTable();
void freeCodetable(char **codeTable);
void getCharacterFrequenciesFromFile(char *filename, int *charFrequencyTable);
int LOOKUP_TESTS();

#endif //HUFFMAN_ENCODER_LOOKUPS_H
