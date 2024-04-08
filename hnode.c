#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode {
    char character;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode();
int height(TreeNode *root);
void freeTree(TreeNode *root);

/**
 * Allocates and returns a default TreeNode
 * @return Pointer to the new TreeNode
 */
TreeNode *createNode() {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->character = 127; // MAX value for character
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Recursively determines the height of the tree
 * @param root Pointer to the root TreeNode
 * @return The height of the tree
 */
int height(TreeNode *root) {
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
void freeTree(TreeNode *root) {
    if (root->left != NULL) {
        freeTree(root -> left);
    }
    if (root->right!= NULL) {
        freeTree(root -> right);
    }
    free(root);
}

/**
 * Returns true if the TreeNode has no children
 * @param node The node to check
 * @return whether the node is a leaf or not as a boolean
 */
int isLeaf(TreeNode *node) {
    return (node -> left == NULL && node -> right == NULL);
}

/**
 * Recursively prints the structure of the tree
 * @param root The root of the tree
 */
void printTree(TreeNode *root) {
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
