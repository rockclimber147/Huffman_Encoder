cmake_minimum_required(VERSION 3.27)
project(Huffman_Encoder C)

set(CMAKE_C_STANDARD 11)

add_executable(Huffman_Encoder hnode.c
        lookups.c
        main.c
        lookups.h
        hnode.h
        createTree.c
        createTree.h
        priorityQueue.c
        priorityQueue.h
        UnitTests.c
        UnitTests.h)
