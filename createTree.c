//
// Created by alexp on 4/5/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "hnode.h"
#include "priorityQueue.h"
#include "lookups.h"

TreeNode* createHuffmanTree(QueueNode** head) {
    while (nodeCount(*head) > 1) {
        // Dequeue two nodes with the lowest frequencies
        QueueNode* node1 = dequeue(head);
        QueueNode* node2 = dequeue(head);

        // Create a new internal node with node1 and node2 as children
        TreeNode* newNode = createNode();
        newNode->left = node1->root;
        newNode->right = node2->root;

        // Enqueue the new node back into the priority queue
        QueueNode* newQueueNode = createQueueNode(newNode, node1->priority + node2->priority);

        *head = enqueue(*head, newQueueNode);

        // Free memory for the dequeued nodes
        free(node1);
        free(node2);
    }

    // The last queueNode in priority queue is the root node of Huffman Tree
    if (*head != NULL) {
        TreeNode* huffmanRoot = (*head)->root;

//        printTree(huffmanRoot);
        return huffmanRoot;
    }

    return NULL; // If the queue is empty
}

/**
 * Generates a priority queue from all nonzero characters and their frequencies in the input table
 * @return a pointer to a priority queue
 */
QueueNode *generatePriorityQueue(int *frequencyTable) {
    QueueNode *newPriorityQueue = NULL;

    for (int i = 0; i < MAX_PRINTABLE_CHARACTERS; i++) {
        if (frequencyTable[i] != 0) {
            // Creating a new tree node for the character
            TreeNode *newRoot = createNode();
            newRoot->character = (char) i;

            // Creating a new queue node
            QueueNode *newQueueNode = createQueueNode(newRoot, frequencyTable[i]);

            // Enqueue the new node into the priority queue
            if (newPriorityQueue == NULL) {
                newPriorityQueue = newQueueNode; // set newQueueNode as head if empty priority queue
            } else {
                newPriorityQueue = enqueue(newPriorityQueue, newQueueNode); // Enqueue in order of priority (frequency)
            }
        }
    }
    return newPriorityQueue;
}