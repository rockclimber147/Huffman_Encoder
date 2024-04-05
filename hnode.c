#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    char character;
    Node *left;
    Node *right;
};

Node *createNode();
int height(Node *root);
void freeTree(Node *root);

Node *createNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->character = 127; // MAX value for character
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(Node *root) {
    if (root == NULL) {
        return -1;
    }
    return (height(root->left) > (height(root->right)))
    ? height(root->left) + 1
    : height(root->right) + 1;
}

void freeTree(Node *root) {
    if (root->left != NULL) {
        freeTree(root -> left);
    }
    if (root->right!= NULL) {
        freeTree(root -> right);
    }
    free(root);
}

