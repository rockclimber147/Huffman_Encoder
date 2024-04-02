#include <stdio.h>
#include <malloc.h>

typedef struct Node Node;
struct Node {
    char value;
    Node *left;
    Node *right;
};

void freeTree(Node *root) {
    if (root->left != NULL) {
        freeTree(root -> left);
    }
    if (root->right!= NULL) {
        freeTree(root -> right);
    }
    free(root);
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
