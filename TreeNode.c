#include <stdio.h>
#include <malloc.h>

typedef struct Node Node;
struct Node {
    char character;
    int *code;
    Node *left;
    Node *right;
};

Node *createNode();
int height(Node *root);
void freeTree(Node *root);

int main() {
    Node *root = createNode();
    root->left = createNode();
    root->right = createNode();
    root->left->left = createNode();
    printf("Height: %d", height(root));
    freeTree(root);
}

Node *createNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->character = 127;
    node -> code = NULL;
    node->left = NULL;
    node->right = NULL;
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

