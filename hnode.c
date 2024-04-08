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

/**
 * Allocates and returns a default Node
 * @return Pointer to the new Node
 */
Node *createNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->character = 127; // MAX value for character
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Recursively determines the height of the tree
 * @param root Pointer to the root Node
 * @return The height of the tree
 */
int height(Node *root) {
    if (root == NULL) {
        return -1;
    }
    return (height(root->left) > (height(root->right)))
    ? height(root->left) + 1
    : height(root->right) + 1;
}

/**
 * Recursively frees all memory allocated to nodes in a tree
 * @param root The root of the tree
 */
void freeTree(Node *root) {
    if (root->left != NULL) {
        freeTree(root -> left);
    }
    if (root->right!= NULL) {
        freeTree(root -> right);
    }
    free(root);
}

/**
 * Returns true if the Node has no children
 * @param node The node to check
 * @return whether the node is a leaf or not as a boolean
 */
int isLeaf(Node *node) {
    return (node -> left == NULL && node -> right == NULL);
}

void printTree(Node *root) {
    if (!root) {
        printf("_");
        return;
    }
    printf("{");
    printTree(root->left);
    printf("|%c|", root->character);
    printTree(root->right);
    printf("}");
}
