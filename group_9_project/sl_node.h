// PROG71985 - Fall 2022 - Group Project
// Group 9: Jonathan Ward, Drasti Patel, Komalpreet Kaur
// Jonathan Ward - based on examples from Prof. Steve Hendrikse

// declarations for NODE of singly-linked list data structure

#pragma once
#include "event.h"

typedef struct node
{
    EVENT data;
    struct node* next;
} NODE;

NODE* createNode(EVENT* event);
void disposeNode(NODE* node);

NODE* getNextNode(NODE* node);
void setNextNode(NODE* sourceNode, NODE* newNextNode);

EVENT* getEventFromNode(NODE* node);
