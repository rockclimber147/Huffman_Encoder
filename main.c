#include <stdio.h>
#include <malloc.h>
#include "lookups.h"
#include "hnode.h"

int main() {
    int *characterFrequencies = getCharacterFrequencies("Hell world!");
    printCharacterFrequencies(characterFrequencies);

    Node *root = createNode();
    root->left = createNode();
    root->left->left = createNode();
    printf("height: %d", height(root));

    freeTree(root);
    free(characterFrequencies);
    return 0;
}

