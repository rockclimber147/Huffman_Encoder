//
// Created by dayle on 2024-04-02.
//

#ifndef HUFFMAN_ENCODER_HNODE_H
#define HUFFMAN_ENCODER_HNODE_H

typedef struct Node Node;
struct Node {
    char character;
    Node *left;
    Node *right;
};

Node *createNode();
int height(Node *root);
void freeTree(Node *root);
int isLeaf(Node *node);
void printTree(Node *root);


#endif //HUFFMAN_ENCODER_HNODE_H
