//
// Created by alexp on 4/5/2024.
//
#include <stdlib.h>
#include "hnode.h"
#include "priorityQueue.h"

Node* createHuffmanTree(QueueNode** head) {
    while (*head != NULL && (*head)->next->next != NULL) {
        // Dequeue two nodes with the lowest frequencies
        QueueNode* node1 = dequeue(head);
        QueueNode* node2 = dequeue(head);

        // Create a new internal node with node1 and node2 as children
        Node* newNode = createNode();
        newNode->left = node1->root;
        newNode->right = node2->root;
        newNode->character = '\0'; // Internal node doesn't represent any character

        // Enqueue the new node back into the priority queue
        QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
        newQueueNode->root = newNode;
        newQueueNode->priority = node1->priority + node2->priority;
        newQueueNode->next = NULL;
        enqueue(head, newQueueNode);

        // Free memory for the dequeued nodes
        freeQueue(node1);
        freeQueue(node2);
    }

    // The last queueNode in priority queue is the root node of Huffman Tree
    if (*head != NULL) {
        Node* huffmanRoot = (*head)->root;
        return huffmanRoot;
    }

    return NULL; // If the queue is empty
}
