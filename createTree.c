//
// Created by alexp on 4/5/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "hnode.h"
#include "priorityQueue.h"
#include "lookups.h"

Node* createHuffmanTree(QueueNode** head) {
    while (nodeCount(*head) > 1) {
        // Dequeue two nodes with the lowest frequencies
        QueueNode* node1 = dequeue(head);
        QueueNode* node2 = dequeue(head);

        // Create a new internal node with node1 and node2 as children
        Node* newNode = createNode();
        newNode->left = node1->root;
        newNode->right = node2->root;

        // Enqueue the new node back into the priority queue
        QueueNode* newQueueNode = createQueueNode(newNode, node1->priority + node2->priority);
        printf("In createHuffmanTree:\n");
        printQueueNode(newQueueNode);
        printf("\n");

        enqueue(*head, newQueueNode);

        // Free memory for the dequeued nodes
        free(node1);
        free(node2);
    }

    // The last queueNode in priority queue is the root node of Huffman Tree
    if (*head != NULL) {
        Node* huffmanRoot = (*head)->root;

        //TODO debug print
        printf("\nprinting completed tree:\n");

        printTree(huffmanRoot);
        return huffmanRoot;
    }

    //TODO debug print
    printf("OH NO! (returning NULL root from createHuffmanTree)\n");

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
            Node *newRoot = createNode();
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