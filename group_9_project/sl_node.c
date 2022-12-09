// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// implementation of NODE for singly-linked list data structure

#include "sl_node.h"
#include <stdlib.h>
#include <stdio.h>

NODE* createNode(EVENT event)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (!newNode)
    {
        fputs("FATAL ERROR: unable to allocate memory\n\n", stderr);
        exit(EXIT_FAILURE);
    }

    newNode->data = copyEvent(event);
    newNode->next = NULL;

    return newNode;
}

void disposeNode(NODE* node)
{
    destroyEvent(&node->data);
    free(node);
}

NODE* getNextNode(NODE* node)
{
    return node->next;
}

void setNextNode(NODE* sourceNode, NODE* newNextNode)
{
    sourceNode->next = newNextNode;
}

EVENT* getEventFromNode(NODE* node)
{
    return &node->data;
}
