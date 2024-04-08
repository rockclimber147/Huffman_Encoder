//
// Created by dayle on 2024-04-02.
//

#ifndef HUFFMAN_ENCODER_HNODE_H
#define HUFFMAN_ENCODER_HNODE_H

typedef struct TreeNode TreeNode;
struct TreeNode {
    char character;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode();
int height(TreeNode *root);
void freeTree(TreeNode *root);
int isLeaf(TreeNode *node);
void printTree(TreeNode *root);


#endif //HUFFMAN_ENCODER_HNODE_H
