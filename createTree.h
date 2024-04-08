//
// Created by alexp on 4/5/2024.
//

#ifndef HUFFMAN_ENCODER_CREATETREE_H
#define HUFFMAN_ENCODER_CREATETREE_H
#include "hnode.h"
#include "priorityQueue.h"

TreeNode* createHuffmanTree(QueueNode** head);
QueueNode *generatePriorityQueue(int *frequencyTable);

#endif //HUFFMAN_ENCODER_CREATETREE_H
