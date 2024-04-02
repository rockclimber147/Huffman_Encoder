//
// Created by dayle on 2024-04-02.
//

#ifndef HUFFMAN_ENCODER_LOOKUPS_H
#define HUFFMAN_ENCODER_LOOKUPS_H
#define MAX_PRINTABLE_CHARACTERS 128

int* getCharacterFrequencies(const char *text);
void printCharacterFrequencies(int *characterFrequencies);

#endif //HUFFMAN_ENCODER_LOOKUPS_H
